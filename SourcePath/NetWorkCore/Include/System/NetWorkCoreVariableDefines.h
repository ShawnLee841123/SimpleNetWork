
#ifndef __NET_WORK_CORE_VARIABLE_DEFINIES_H__
#define __NET_WORK_CORE_VARIABLE_DEFINIES_H__

#ifdef WIN32
#include <WinSock2.h>

#define CORE_SOCKET SOCKET
#define CORE_SOCKETADDR_IN SOCKADDR_IN
#define CORE_SOCKETADDR SOCKADDR

#else

#endif

#define IO_BUFF_SIZE 2014

#define LISTEN_LINK_MAX 4096

union Core_SockAddress
{
	unsigned char m_strAdd[4];
	unsigned long long m_lAdd = 0llu;

	Core_SockAddress()
	{}

	Core_SockAddress(char a, char b, char c, char d)
	{
		m_strAdd[0] = a;
		m_strAdd[1] = b;
		m_strAdd[2] = c;
		m_strAdd[3] = d;
	}

	Core_SockAddress(unsigned long long lAdd)
	{
		m_lAdd = lAdd;
	}

	Core_SockAddress& operator=(const Core_SockAddress& rhv)
	{
		m_lAdd = rhv.m_lAdd;
		return *this;
	}
};

static inline bool operator<(Core_SockAddress const& lhv, Core_SockAddress const& rhv)
{
	return lhv.m_lAdd < rhv.m_lAdd;
}

static inline bool operator==(Core_SockAddress const& lhv, Core_SockAddress const& rhv)
{
	return lhv.m_lAdd == rhv.m_lAdd;
}

struct Core_SockStoreKey
{
	Core_SockAddress		m_rAddress;
	unsigned int			m_uPort;

	Core_SockStoreKey()
	{
		m_rAddress.m_lAdd = 0llu;
		m_uPort = 0;
	}

	Core_SockStoreKey(unsigned long long lAdd, int nPort)
	{
		m_rAddress.m_lAdd = lAdd;
		m_uPort = nPort;
	}

	Core_SockStoreKey& operator=(const Core_SockStoreKey& rhv)
	{
		m_rAddress = rhv.m_rAddress;
		m_uPort = rhv.m_uPort;
		return *this;
	}
};

static inline bool operator<(Core_SockStoreKey const& lhv, Core_SockStoreKey const& rhv)
{
	return (lhv.m_rAddress< rhv.m_rAddress)
		|| ((lhv.m_rAddress == rhv.m_rAddress) && (lhv.m_uPort < rhv.m_uPort));
}

static inline bool operator==(Core_SockStoreKey const& lhv, Core_SockStoreKey const& rhv)
{
	return ((lhv.m_rAddress == rhv.m_rAddress) && (lhv.m_uPort == rhv.m_uPort));
}



#endif	//	__NET_WORK_CORE_VARIABLE_DEFINIES_H__
