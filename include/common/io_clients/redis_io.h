//
// Created by Jie on 8/25/20.
// It is the implementation of Redis IO
//

#ifndef COMMON_REDIS_IO_H
#define COMMON_REDIS_IO_H

#include <common/io_clients/io.h>

#ifdef ENABLE_REDIS_IOCLIENT
#include <sw/redis++/redis++.h>

using namespace sw::redis;

#endif
class RedisIOClient: public IOClient {
private:
    std::vector<std::string> split(const std::string& s, char delimiter)
    {
        std::vector<std::string> tokens;
        std::string token;
        std::istringstream tokenStream(s);
        while (std::getline(tokenStream, token, delimiter))
        {
            tokens.push_back(token);
        }
        return tokens;
    }
public:
    /*
     * Constructor
     */
    RedisIOClient(uint16_t storage_index):IOClient(storage_index){
#ifdef ENABLE_REDIS_IOCLIENT
        auto redis_solution = std::static_pointer_cast<RedisSS>(solution);
        ConnectionOptions connectionOptions;
        std::string end_points(redis_solution->end_point_.c_str());
        auto end_points_arr = split(end_points,',');
        std::string ports(redis_solution->port_.c_str());
        auto ports_arr = split(ports,',');
        auto index = BASKET_CONF->MPI_RANK % end_points_arr.size();
        connectionOptions.host = end_points_arr[index]; // redis_cluster ip
        connectionOptions.port = atoi(ports_arr[index].c_str()); // redis_cluster port
        try {
            m_redisCluster = std::make_shared<RedisCluster>(connectionOptions);
        }catch (const Error &err){
            throw ErrorException(CONNECT_REDIS_SERVER_ERROR);
        }
#endif
    }
    /*
     * Methods
     */

    /*
     * Read data from source into destination buffer while respecting the position_
     */
    void Read(Data &source, Data &destination) override;

    bool Remove(Data &source) override;

    /*
     * Write data from source into destination buffer while respecting the position_
     */
    void Write(Data &source, Data &destination) override;

    size_t Size(Data &source) override;

private:
#ifdef ENABLE_REDIS_IOCLIENT
    std::shared_ptr<RedisCluster>   m_redisCluster;
#endif
};

#endif //COMMON_REDIS_IO_H
