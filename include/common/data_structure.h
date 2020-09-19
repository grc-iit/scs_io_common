//
// Created by Jie on 8/26/20.
// Define the data structures used in
//

#ifndef COMMON_DATA_STRUCTURE_H
#define COMMON_DATA_STRUCTURE_H

#include <basket/common/data_structures.h>
#include <rpc/msgpack.hpp>
#include <common/enumerations.h>
#include <iostream>

typedef struct Data{
    CharStruct id_; // for file io, the "id_" is the filename; for object store io, the "id_" is the key.
    size_t position_; // read/write start position
    char* buffer_;  // data content
    size_t data_size_;
    uint16_t storage_index_;

    /*Define the default, copy and move constructor*/
    Data(): id_(), position_(0), buffer_(NULL), storage_index_(),data_size_(){}
    Data(CharStruct id, size_t position, char *buffer, uint16_t storage_index, size_t data_size): id_(id),
            position_(position), buffer_(buffer), storage_index_(storage_index),data_size_(data_size){}
    Data(const Data &other): id_(other.id_), position_(other.position_), buffer_(other.buffer_),
                             storage_index_(other.storage_index_),data_size_(other.data_size_) {}
    Data(Data &other): id_(other.id_), position_(other.position_), buffer_(other.buffer_),
                      storage_index_(other.storage_index_),data_size_(other.data_size_) {}

    /*Define Assignment Operator*/
    Data &operator=(const Data &other){
        id_ = other.id_;
        position_ = other.position_;
        buffer_ = other.buffer_;
        data_size_ = other.data_size_;
        storage_index_ = other.storage_index_;
        return *this;
    }
} Data;

typedef struct StorageSolution{
    CharStruct end_point_;
    IOClientType io_client_type_;
    /*Define the default, copy and move constructor*/
    StorageSolution(): end_point_(), io_client_type_(){}
    StorageSolution(CharStruct end_point, IOClientType io_client_type): end_point_(end_point), io_client_type_(io_client_type){}
    StorageSolution(const StorageSolution &other): end_point_(other.end_point_),
                                                   io_client_type_(other.io_client_type_){}
    StorageSolution(StorageSolution &other): end_point_(other.end_point_),
                                             io_client_type_(other.io_client_type_){}

    /*Define Assignment Operator*/
    StorageSolution &operator=(const StorageSolution &other){
        end_point_ = other.end_point_;
        io_client_type_ = other.io_client_type_;
        return *this;
    }
} StorageSolution;

typedef struct FileSS: public StorageSolution{
    /*Define the default, copy and move constructor*/
    FileSS(CharStruct end_point): StorageSolution(end_point,IOClientType::FILE_IO){}
    FileSS(const FileSS &other): StorageSolution(other){}
    FileSS(FileSS &other): StorageSolution(other){}
    /*Define Assignment Operator*/
    FileSS &operator=(const FileSS &other){
        StorageSolution::operator=(other);
        return *this;
    }
}FileStorageSolution;

typedef struct RedisSS: public StorageSolution{
    std::string port_;
    /*Define the default, copy and move constructor*/
    RedisSS(CharStruct end_point,  std::string port):StorageSolution(end_point,IOClientType::REDIS_IO),port_(port){}
    RedisSS(const RedisSS &other):StorageSolution(other),port_(other.port_){}
    RedisSS(RedisSS &other):StorageSolution(other),port_(other.port_){}
    /*Define Assignment Operator*/
    RedisSS &operator=(const RedisSS &other){
        StorageSolution::operator=(other);
        port_=other.port_;
        return *this;
    }
}RedisSS;

typedef struct MongoSS: public StorageSolution{
    CharStruct database_;
    CharStruct collection_;
    /*Define the default, copy and move constructor*/
    MongoSS(CharStruct end_point,CharStruct database,CharStruct collection):StorageSolution(end_point,IOClientType::MONGO_IO),database_(database),collection_(collection){}
    MongoSS(const MongoSS &other):StorageSolution(other),database_(other.database_),collection_(other.collection_){}
    MongoSS(MongoSS &other):StorageSolution(other),database_(other.database_),collection_(other.collection_){}
    /*Define Assignment Operator*/
    MongoSS &operator=(const MongoSS &other){
        StorageSolution::operator=(other);
        database_=other.database_;
        collection_=other.collection_;
        return *this;
    }
}MongoSS;


typedef struct DataDistribution{
   Data source_data_; // memory buffer for write and file buffer for read
   Data destination_data_; // file info for write and memory info for read
   uint16_t storage_index_; // native io client_service type

   /*Define the default, copy and move constructor*/
   DataDistribution(): storage_index_(), destination_data_(), source_data_(){}
   DataDistribution(const DataDistribution &other): source_data_(other.source_data_),
                                                    destination_data_(other.destination_data_), storage_index_(other.storage_index_){}
   DataDistribution(DataDistribution &other): source_data_(other.source_data_),
                                              destination_data_(other.destination_data_), storage_index_(other.storage_index_){}

   /*Define Assignment Operator*/
   DataDistribution &operator=(const DataDistribution &other){
       source_data_ = other.source_data_;
       destination_data_ = other.destination_data_;
       storage_index_ = other.storage_index_;
       return *this;
   }
} DataDistribution;

typedef struct Metadata{
   bool is_link_;
   uint16_t storage_index_;
   std::unordered_map<int64_t , Data> links_;
   /*Define the default, copy and move constructor*/
   Metadata(): is_link_(), links_(),storage_index_(){}
   Metadata(const Metadata &other): is_link_(other.is_link_),
                                    links_(other.links_),
                                    storage_index_(other.storage_index_){}
   Metadata(Metadata &other): is_link_(other.is_link_),
                              links_(other.links_),
                              storage_index_(other.storage_index_){}

   /*Define Assignment Operator*/
   Metadata &operator=(const Metadata &other){
       is_link_ = other.is_link_;
       links_ = other.links_;
       storage_index_=other.storage_index_;
       return *this;
   }
} Metadata;

#include <rpc/msgpack.hpp>
namespace clmdep_msgpack {
    MSGPACK_API_VERSION_NAMESPACE(MSGPACK_DEFAULT_API_NS) {
        namespace adaptor {
            namespace mv1 = clmdep_msgpack::v1;
            template<>
            struct convert<Metadata> {
                mv1::object const &operator()(mv1::object const &o, Metadata &input) const {
                    input.is_link_ = o.via.array.ptr[0].as<bool>();
                    input.links_ = o.via.array.ptr[1].as<std::unordered_map<int64_t, Data>>();
                    input.storage_index_ = o.via.array.ptr[2].as<uint16_t>();
                    return o;
                }
            };

            template<>
            struct pack<Metadata> {
                template<typename Stream>
                packer <Stream> &operator()(mv1::packer <Stream> &o, Metadata const &input) const {
                    o.pack_array(3);
                    o.pack(input.is_link_);
                    o.pack(input.links_);
                    o.pack(input.storage_index_);
                    return o;
                }
            };

            template<>
            struct object_with_zone<Metadata> {
                void operator()(mv1::object::with_zone &o, Metadata const &input) const {
                    o.type = type::ARRAY;
                    o.via.array.size = 3;
                    o.via.array.ptr = static_cast<clmdep_msgpack::object *>(o.zone.allocate_align(
                            sizeof(mv1::object) * o.via.array.size, MSGPACK_ZONE_ALIGNOF(mv1::object)));
                    o.via.array.ptr[0] = mv1::object(input.is_link_, o.zone);
                    o.via.array.ptr[1] = mv1::object(input.links_, o.zone);
                    o.via.array.ptr[2] = mv1::object(input.storage_index_, o.zone);
                }
            };
            template<>
            struct convert<Data> {
                mv1::object const &operator()(mv1::object const &o, Data &input) const {
                    input.id_ = o.via.array.ptr[0].as<CharStruct>();
                    input.position_ = o.via.array.ptr[1].as<size_t>();
                    auto data = o.via.array.ptr[2].as<std::string>();
                    input.data_size_ = o.via.array.ptr[3].as<size_t>();
                    if(!data.empty()) {
                        input.buffer_= static_cast<char *>(malloc(input.data_size_));
                        memcpy(input.buffer_ , data.data(),input.data_size_);
                    }
                    input.storage_index_ = o.via.array.ptr[4].as<uint16_t>();
                    return o;
                }
            };

            template<>
            struct pack<Data> {
                template<typename Stream>
                packer <Stream> &operator()(mv1::packer <Stream> &o, Data const &input) const {
                    o.pack_array(5);
                    o.pack(input.id_);
                    o.pack(input.position_);
                    if(input.buffer_ == NULL) o.pack(std::string());
                    else {
                        o.pack(std::string(input.buffer_,input.data_size_));
                    }
                    o.pack(input.data_size_);
                    o.pack(input.storage_index_);
                    return o;
                }
            };

            template<>
            struct object_with_zone<Data> {
                void operator()(mv1::object::with_zone &o, Data const &input) const {
                    o.type = type::ARRAY;
                    o.via.array.size = 5;
                    o.via.array.ptr = static_cast<clmdep_msgpack::object *>(o.zone.allocate_align(
                            sizeof(mv1::object) * o.via.array.size, MSGPACK_ZONE_ALIGNOF(mv1::object)));
                    o.via.array.ptr[0] = mv1::object(input.id_, o.zone);
                    o.via.array.ptr[1] = mv1::object(input.position_, o.zone);
                    if(input.buffer_ == NULL) o.via.array.ptr[2] = mv1::object(std::string(), o.zone);
                    else {
                        o.via.array.ptr[2] = mv1::object(std::string(input.buffer_,input.data_size_), o.zone);
                        free(input.buffer_);
                    }
                    o.via.array.ptr[3] = mv1::object(input.data_size_, o.zone);
                    o.via.array.ptr[4] = mv1::object(input.storage_index_, o.zone);
                }
            };
        }  // namespace adaptor
    }
}  // namespace clmdep_msgpack
std::ostream &operator<<(std::ostream &os, Data &data);
std::ostream &operator<<(std::ostream &os, Metadata &d);
std::ostream &operator<<(std::ostream &os, DataDistribution &m);

#endif //COMMON_DATA_STRUCTURE_H

