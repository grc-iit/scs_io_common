//
// Created by Jie on 8/25/20.
//

#include <common/debug.h>
#include <basket/common/singleton.h>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#include <common/debug.h>
#include <cstring>
#include <mongocxx/exception/bulk_write_exception.hpp>
#include <mongocxx/exception/query_exception.hpp>
#include <string>
#include <common/configuration_manager.h>
#include <common/error_codes.h>
#include <common/io_clients/mongo_io.h>

void MongoIOClient::Read(Data &source, Data &destination) {
  AUTO_TRACER("MongoIOClient::Read", source, destination);
mongocxx::collection file = client[mongo_solution->database_.c_str()].collection(
            mongo_solution->collection_.c_str());
    bsoncxx::stdx::optional<bsoncxx::document::value> maybe_result =
            file.find_one(bsoncxx::builder::stream::document{} << "key" << std::string(source.id_.c_str())
                                                               << bsoncxx::builder::stream::finalize);
    if (maybe_result) {
        auto data = maybe_result->view()["value"].get_utf8().value.to_string();
        size_t source_size = source.data_size_;
        if(source_size == 0){
            source_size = data.size();
        }
        destination.buffer_= static_cast<char *>(malloc(source_size - source.position_) );
        memcpy(destination.buffer_,data.data()+source.position_,source_size - source.position_);
        destination.data_size_ = source_size - source.position_;
    } else {
        throw ErrorException(READ_MONGODB_DATA_FAILED);
    }
    COMMON_DBGVAR(destination);
}

void MongoIOClient::Write(Data &source, Data &destination) {
    AUTO_TRACER("MongoIOClient::Write", source,destination);
    mongocxx::collection file = client[mongo_solution->database_.c_str()].collection(
            mongo_solution->collection_.c_str());
    bool exists = false;
    Data read_source;
    std::string new_val;
    try {
        read_source.id_ = destination.id_;
        Read(read_source, read_source);
        exists = true;
    } catch (const std::exception &e) {
        exists = false;
    }
    if (exists) {
        if (source.data_size_ - source.position_ >= read_source.data_size_ || source.data_size_ - source.position_ + destination.position_ >= read_source.data_size_) {
            new_val=std::string();
            new_val.resize(destination.position_ + source.data_size_ - source.position_);
            if (destination.position_ > 0) {
                memcpy(new_val.data(), read_source.buffer_, destination.position_ - 1);
            }
            memcpy(new_val.data() + destination.position_, source.buffer_ + source.position_, source.data_size_ - source.position_);
            source.position_ = 0;
        } else {
            new_val=std::string(read_source.buffer_,read_source.data_size_);
            // update the old_value
            memcpy(new_val.data() + destination.position_,
                   source.buffer_ + source.position_,
                   source.data_size_ - source.position_);
            source.position_ = 0;
        }
        file.delete_many(bsoncxx::builder::basic::make_document(
                bsoncxx::builder::basic::kvp("key", std::string(destination.id_.c_str()))));
        free(read_source.buffer_);
    }else{
        new_val=std::string(source.buffer_,source.data_size_);
    }
    auto document = bsoncxx::builder::basic::document{};
    using bsoncxx::builder::basic::kvp;
    std::string data(new_val.data() + source.position_, source.data_size_ - source.position_);
    std::string keyName(destination.id_.c_str());
    //std::cout<<"KeyName :"<<keyName<<"\n";
    document.append(kvp("key", keyName), kvp("value", data));

    //adding the created key-value pair to the collection
    bsoncxx::document::view putView = document.view();//get the view
    //retrieve the unique objectID from map
    auto add = file.insert_one(putView);//insert it to collection
    if (!add) {
        std::cout << "Unacknowledged write. No id available." << "\n";
    }
    if (add->inserted_id().type() == bsoncxx::type::k_oid) {
        bsoncxx::oid id = add->inserted_id().get_oid().value;
        COMMON_DBGVAR(id.to_string());
    } else std::cout << "Inserted id was not an OID type" << "\n";
}

bool MongoIOClient::Remove(Data &source) {
    AUTO_TRACER("MongoIOClient::Remove", source);
    mongocxx::collection file = client[mongo_solution->database_.c_str()].collection(
            mongo_solution->collection_.c_str());
    file.delete_many(bsoncxx::builder::basic::make_document(
            bsoncxx::builder::basic::kvp("key", std::string(source.id_.c_str()))));
    return true;
}

size_t MongoIOClient::Size(Data &source) {
    bool exists = false;
    Data read_source;
    try {
        read_source.id_ = source.id_;
        Read(read_source, read_source);
        return read_source.data_size_;
    } catch (const std::exception &e) {
       return 0;
    }
}
