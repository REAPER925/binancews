#pragma once

#include <sw/redis++/redis.h>
#include <functional>
#include "Logger.hpp"


namespace binancews
{
    using std::shared_ptr;
    using std::string;


    class Redis
    {
    public:
        Redis()
        {

        }


         //void init(const std::string& ip, const int port)
        void init()
        {
            sw::redis::ConnectionPoolOptions poolOptions;
            poolOptions.size = std::thread::hardware_concurrency();
            sw::redis::ConnectionOptions connOptions;
            connOptions.type = sw::redis::ConnectionType::TCP;
            connOptions.connect_timeout = std::chrono::milliseconds(100);   // Required.
            connOptions.socket_timeout = std::chrono::milliseconds(100);    // Required.        /conn


            sw::redis::SentinelOptions sentinel_opts;
            sentinel_opts.nodes = {{"192.168.100.18", 26379},
                                    {"192.168.100.12", 26379},
                                    {"192.168.100.30", 26379}};   // Required. List of Redis Sentinel nodes.

            sentinel_opts.connect_timeout = std::chrono::milliseconds(200);
            sentinel_opts.socket_timeout = std::chrono::milliseconds(200);
            auto sentinel = std::make_shared<sw::redis::Sentinel>(sentinel_opts);

            //auto m_redis = sw::redis::Redis(sentinel, "mymaster", sw::redis::Role::MASTER, connOptions, poolOptions);

            m_redis = std::make_shared<sw::redis::Redis>(sentinel, "mymaster", sw::redis::Role::MASTER, connOptions, poolOptions);
            // m_redis = std::make_shared<sw::redis::Redis>(connOptions, poolOptions);
        }


        void set(const std::string& k, const std::string& v)
        {
            try
            {
                m_redis->set(k, v);
            }
            catch (std::exception ex)
            {
                logg(ex.what());
            }            
        }

        void publish(const string& channel, const string& msg)
        {
            m_redis->publish(channel, msg); // TODO return value useful?
        }

    private:
        shared_ptr<sw::redis::Redis> m_redis;
    };
}
