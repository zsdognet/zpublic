// Generate by the sword of core(核心之刃). DO NOT EDIT!
// Source : protocol.h
// Comment : 通信消息协议文件。

#ifndef __PROTOCOL_H__
#define __PROTOCOL_H__

#include <venus_net/venus_net.h>

namespace Protocol
{
    static uint32 getStrListSize(const std::vector<std::string>& strList) 
    {
        uint32 size = 0; 
        for (uint32 i = 0; i < strList.size(); i++) 
        { 
            size += strList[i].length() + 2; 
        }

        return size + 2;
    }

    template<class T> 
    static uint32 getStructArrBytesSize(const std::vector<T>& vt)
    {
        uint32 size = 0; 
        for (uint32 i = 0; i < vt.size(); i++) 
        { 
            size += vt[i].byteSize(); 
        }

        return 2 + size;
    }

    /**
    * ● 注册登录(4 message)
    */

    //登录请求
    struct CSLoginReq : public NetworkMessage
    {
        //登录帐号（邮箱地址）
        std::string account;
        //密码
        std::string password;

        int byteSize()
        {
            return (account.length() + 2) + (password.length() + 2);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << account;
            w << password;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> account;
            r >> password;
        }
    };

    //登录返回
    struct SCLoginRsp : public NetworkMessage
    {
        //登录结果
        uint8 login_result;
        //角色ID
        uint64 player_id;

        int byteSize()
        {
            return sizeof(login_result) + sizeof(player_id);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << login_result;
            w << player_id;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> login_result;
            r >> player_id;
        }
    };

    //用户注册请求
    struct CSRegisterReq : public NetworkMessage
    {
        //要注册的用户名
        std::string username;
        //密码
        std::string password;

        int byteSize()
        {
            return (username.length() + 2) + (password.length() + 2);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << username;
            w << password;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> username;
            r >> password;
        }
    };

    //用户注册返回
    struct SCRegisterRsp : public NetworkMessage
    {
        //注册结果（true-成功， false-失败）
        uint8 register_result;

        int byteSize()
        {
            return sizeof(register_result);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << register_result;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> register_result;
        }
    };

    /**
    * ● 背包(4 message)
    */

    //背包列表请求
    struct CSBagList : public NetworkMessage
    {
        //背包类型(0 - 包裹，1 - 仓库)
        uint8 m_nBagType;

        int byteSize()
        {
            return sizeof(m_nBagType);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << m_nBagType;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> m_nBagType;
        }
    };

    //背包列表返回
    struct SCBagList : public NetworkMessage
    {
        //格子数量
        uint8 m_nCellNum;

        int byteSize()
        {
            return sizeof(m_nCellNum);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << m_nCellNum;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> m_nCellNum;
        }
    };

    //整理背包请求
    struct CSBagResort : public NetworkMessage
    {
        //背包类型(0 - 包裹，1 - 仓库)
        uint8 m_nBagType;

        int byteSize()
        {
            return sizeof(m_nBagType);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << m_nBagType;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> m_nBagType;
        }
    };

    //整理背包返回
    struct SCBagResort : public NetworkMessage
    {
        //返回码(0 - 成功，> 0 失败原因)
        uint8 m_nResult;

        int byteSize()
        {
            return sizeof(m_nResult);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << m_nResult;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> m_nResult;
        }
    };

    /**
    * ● 英雄(卡牌)(0 message)
    */

    /**
    * ● test(2 message)
    */

    struct CSTestPacketReq : public NetworkMessage
    {
        uint32 uint_value;
        std::string string_value;

        int byteSize()
        {
            return sizeof(uint_value) + (string_value.length() + 2);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << uint_value;
            w << string_value;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> uint_value;
            r >> string_value;
        }
    };

    struct SCTestPacketRsp : public NetworkMessage
    {
        uint32 srv_uint_value;
        std::string srv_string_value;

        int byteSize()
        {
            return sizeof(srv_uint_value) + (srv_string_value.length() + 2);
        }

        void encode(byte* buffer, size_t size)
        {
            StreamWriter w(buffer, size);
            w << srv_uint_value;
            w << srv_string_value;
        }

        void decode(const byte* buffer, size_t size)
        {
            StreamReader r(buffer, size);
            r >> srv_uint_value;
            r >> srv_string_value;
        }
    };

}

#endif    //__PROTOCOL_H__