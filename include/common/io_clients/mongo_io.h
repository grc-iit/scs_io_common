//
// Created by Jie on 8/25/20.
// It is the implementation of Mongo IO
//

#ifndef COMMON_MONGO_IO_H
#define COMMON_MONGO_IO_H

#include <common/io_clients/io.h>

#include <memory>
#include <common/debug.h>
#include <basket/common/singleton.h>
#include <common/debug.h>
#include <cstring>
#include <string>
#include <common/configuration_manager.h>
#include <common/error_codes.h>
#include "io.h"

#ifdef ENABLE_MONGO_CLIENT
#include <bsoncxx/json.hpp>
#include <mongocxx/client_service.hpp>
#include <mongocxx/stdx.hpp>
#include <mongocxx/uri.hpp>
#include <mongocxx/instance.hpp>
#include <bsoncxx/builder/basic/document.hpp>
#include <mongocxx/logger.hpp>
#include <bsoncxx/stdx/make_unique.hpp>
#include <mongocxx/exception/exception.hpp>
#include <mongocxx/exception/bulk_write_exception.hpp>
#include <mongocxx/exception/query_exception.hpp>
#include <bsoncxx/builder/stream/document.hpp>
#include <bsoncxx/builder/stream/helpers.hpp>
#endif

class MongoIOClient: public IOClient {
public:
    /*
     * Constructor
     */
    MongoIOClient(uint16_t storage_index):IOClient(storage_index){
#ifdef ENABLE_MONGO_CLIENT
        mongo_solution = std::static_pointer_cast<MongoSS>(solution);
        class noop_logger : public mongocxx::logger {
        public:
            virtual void operator()(mongocxx::log_level,
                                    mongocxx::stdx::string_view,
                                    mongocxx::stdx::string_view) noexcept {}
        };
        /* Setup the MongoDB client_service */
        mongocxx::instance instance{mongocxx::stdx::make_unique<noop_logger>()};
        auto uri = mongocxx::uri{mongo_solution->end_point_.c_str()};
        try {
            client_service = mongocxx::client_service{uri};
            /* make sure the client_service is OK */
            if (!client_service) {
                fprintf(stderr, "Cannot create MongoDB client_service.\n");
                throw ErrorException(CREATE_MONGO_CLIENT_ERROR);
            }
            mongocxx::database db = client_service[mongo_solution->database_.c_str()];
            if (!db) {
                fprintf(stderr, "Cannot connect to MongoDB database.\n");
                throw ErrorException(CONNECT_MONGO_DATABASE_ERROR);
            }
            mongocxx::collection file;
            if(BASKET_CONF->MPI_RANK==0) {
                file = client_service.database(mongo_solution->database_.c_str()).has_collection(mongo_solution->collection_.c_str()) ?
                   db.collection(mongo_solution->collection_.c_str()) :
                   db.create_collection(mongo_solution->collection_.c_str());
            }
            file = db.collection(mongo_solution->collection_.c_str());
            if (!file) {
                fprintf(stderr, "Cannot connect to MongoDB collection.\n");
                throw ErrorException(CONNECT_MONGO_COLLECTION_ERROR);
            }
        } catch (const mongocxx::exception& e){
            throw ErrorException(CONNECT_MONGO_SERVER_ERROR);
        }
#endif
    }
    /*
     * Methods
     */

    /*
     * Reads data from source into destination buffer while respecting the position_
     */
    void Read(Data &source, Data &destination) override;

    /*
     * Writes data from source into destination buffer while respecting the position_
     */
    void Write(Data &source, Data &destination) override;

    bool Remove(Data &source) override;

    size_t Size(Data &source) override;

private:
#ifdef ENABLE_MONGO_CLIENT
    mongocxx::client_service client_service;
#endif
    std::shared_ptr<MongoSS> mongo_solution;
};

#endif //COMMON_MONGO_IO_H
