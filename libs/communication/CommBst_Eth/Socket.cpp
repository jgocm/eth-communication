#include "Socket.h"
#include <errno.h> 
#include <cstring>
#include <fcntl.h>
#include<iostream>
#include<cstdlib>
#include<cstdio>
#include<pthread.h>
#include <unistd.h>
#include "Mutex.h"
#define BUF_SIZE 1024
CSocketException::CSocketException( const string &sMessage, bool blSysMsg /*= false*/ ) throw() :m_sMsg(sMessage)
{
    if (blSysMsg) {
        m_sMsg.append(": ");
        m_sMsg.append(strerror(errno));
    }
}
 
CSocketException::~CSocketException() throw ()
{
 
}
 
CSocket::~CSocket()
{
    ::close(m_sockDesc);
    m_sockDesc = -1;
}
 
CSocket::CSocket( SocketType type, NetworkLayerProtocol protocol ) throw(CSocketException):m_sockDesc(-1)
{
    m_sockDesc = socket(protocol, type, 0);
    if (m_sockDesc < 0)
    {
        throw CSocketException("Socket creation failed (socket())", true);
    }
}
 
CSocket::CSocket( int sockDesc )
{
    m_sockDesc = sockDesc;
}
 
CSocket::CSocket( const CSocket &sock )
{
 
}
 
void CSocket::operator=( const CSocket &sock )
{
 
}
 
std::string CSocket::GetLocalAddress() throw(CSocketException)
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);
 
    if (getsockname(m_sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
        throw CSocketException("Fetch of local address failed (getsockname())", true);
    }
    return inet_ntoa(addr.sin_addr);
}
 
unsigned short CSocket::GetLocalPort() throw(CSocketException)
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);
 
    if (getsockname(m_sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
        throw CSocketException("Fetch of local port failed (getsockname())", true);
    }
    return ntohs(addr.sin_port);
}
 
void CSocket::BindLocalPort( unsigned short localPort ) throw(CSocketException)
{
    // Bind the socket to its port
    sockaddr_in localAddr;
    memset(&localAddr, 0, sizeof(localAddr));
    localAddr.sin_family = AF_INET;
    localAddr.sin_addr.s_addr = htonl(INADDR_ANY);
    localAddr.sin_port = htons(localPort);
 
    if (bind(m_sockDesc, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0) {
        throw CSocketException("Set of local port failed (bind())", true);
    }
}
 
void CSocket::BindLocalAddressAndPort( const string &localAddress, unsigned short localPort /*= 0*/ )
    throw(CSocketException)
{
    // Get the address of the requested host
    sockaddr_in localAddr;
    FillAddr(localAddress, localPort, localAddr);
 
    if (bind(m_sockDesc, (sockaddr *) &localAddr, sizeof(sockaddr_in)) < 0) {
        throw CSocketException("Set of local address and port failed (bind())", true);
    }
}
 
void CSocket::FillAddr( const string & localAddress, unsigned short localPort, sockaddr_in& localAddr )
{
    ////cout<<"\n Inside Fille addr:"<<localAddress <<" port:"<<localPort;
    memset(&localAddr, 0, sizeof(localAddr));  // Zero out address structure
    localAddr.sin_family = AF_INET;       // Internet address
 
    hostent *host;  // Resolve name
    if ((host = gethostbyname(localAddress.c_str())) == NULL) {
        // strerror() will not work for gethostbyname() and hstrerror() 
        // is supposedly obsolete
        throw CSocketException("Failed to resolve name (gethostbyname())");
    }
    localAddr.sin_addr.s_addr = *((unsigned long *) host->h_addr_list[0]);
 
    localAddr.sin_port = htons(localPort);     // Assign port in network byte order
    ////cout<<"\n returning from  Fille addr";
}
 
unsigned long int CSocket::GetReadBufferSize()
{
    unsigned long int nSize;
    socklen_t n = sizeof(nSize);
    getsockopt(m_sockDesc,SOL_SOCKET,SO_RCVBUF,(void *)&nSize, (&n));
    // now the variable nSize will have the socket size
    return nSize; 
}
 
void CSocket::SetReadBufferSize( unsigned int nSize ) throw(CSocketException)
{
    if (setsockopt(m_sockDesc, SOL_SOCKET, SO_RCVBUF, &nSize, sizeof(nSize)) == -1) 
    {
        throw CSocketException("Error in setting socket buffer size ", true);
    }
}
 
void CSocket::SetNonBlocking( bool bBlocking ) throw(CSocketException)
{
    int opts;
 
    opts = fcntl ( m_sockDesc, F_GETFL );
 
    if ( opts < 0 )
    {
        return;
    }
 
    if ( bBlocking )
        opts = ( opts | O_NONBLOCK );
    else
        opts = ( opts & ~O_NONBLOCK );
 
    fcntl ( m_sockDesc, F_SETFL,opts );
}
 
void CSocket::ConnectToHost( const string &foreignAddress, unsigned short foreignPort ) throw(CSocketException)
{
    //cout<<"\nstart Connect to host";
    // Get the address of the requested host
    sockaddr_in destAddr;
    //cout<<"\ninside Connect to host";
    FillAddr(foreignAddress, foreignPort, destAddr);
 
    //cout<<"trying to connect to host";
    // Try to connect to the given port
    if (::connect(m_sockDesc, (sockaddr *) &destAddr, sizeof(destAddr)) < 0) {
        throw CSocketException("Connect failed (connect())", true);
    }
    //cout<<"\n after connecting";
 
}
 
void CSocket::Send( const void *buffer, int bufferLen ) throw(CSocketException)
{
    if (::send(m_sockDesc, (void *) buffer, bufferLen, 0) < 0) {
        throw CSocketException("Send failed (send())", true);
    }
}
 
int CSocket::Recv( void *buffer, int bufferLen ) throw(CSocketException)
{
    int nBytes;
    if ((nBytes = ::recv(m_sockDesc, (void *) buffer, bufferLen, 0)) < 0) {
        throw CSocketException("Received failed (recv())", true);
    }
    char* sData = static_cast<char *>(buffer);
    sData[nBytes] = '\0';
    return nBytes;
}
 
std::string CSocket::GetPeerAddress() throw(CSocketException)
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);
 
    if (getpeername(m_sockDesc, (sockaddr *) &addr,(socklen_t *) &addr_len) < 0) {
        throw CSocketException("Fetch of foreign address failed (getpeername())", true);
    }
    return inet_ntoa(addr.sin_addr);
}
 
unsigned short CSocket::GetPeerPort() throw(CSocketException)
{
    sockaddr_in addr;
    unsigned int addr_len = sizeof(addr);
 
    if (getpeername(m_sockDesc, (sockaddr *) &addr, (socklen_t *) &addr_len) < 0) {
        throw CSocketException("Fetch of foreign port failed (getpeername())", true);
    }
    return ntohs(addr.sin_port);
}
 
CSocket& CSocket::operator<<(const string& sStr )
{
     Send(sStr.c_str(), sStr.length());
     return *this;
}
 
CSocket& CSocket::operator>>( string& sStr )
{
    char *buff = new char[GetReadBufferSize()];
    Recv(buff, GetReadBufferSize());
    sStr.append(buff);
    delete [] buff;
    return *this;
}
 
int CSocket::OnDataRead(unsigned long timeToWait)
{
    /* master file descriptor list */
    fd_set master;
    struct timeval      *ptimeout = NULL;
 
    /* temp file descriptor list for select() */
    fd_set read_fds;
 
    /* maximum file descriptor number */
    int fdmax;
 
    /* clear the master and temp sets */
    FD_ZERO(&master);
    FD_ZERO(&read_fds);
 
    /* add the listener to the master set */
    FD_SET(m_sockDesc, &master);
    /* keep track of the biggest file descriptor */
    fdmax = m_sockDesc; /* so far, it's this one*/
 
    /* copy it */
    read_fds = master;
    //cout<<"Waiting for select";
    int nRet;
    if (timeToWait == ULONG_MAX)
    {
        nRet  = select(fdmax+1, &read_fds, NULL, NULL, NULL);
        if (nRet == -1)
            nRet = DATA_EXCEPTION;
        else if (nRet > 0)
            nRet = DATA_ARRIVED;
    }
    else
    {
        struct timeval       timeout;
        timeout.tv_sec  = timeToWait;
        timeout.tv_usec = 0;
        nRet = select(fdmax+1, &read_fds, NULL, NULL, &timeout);
        if (nRet == -1)
            nRet = DATA_EXCEPTION;
        else if (nRet > 0)
            nRet = DATA_ARRIVED;
        else if(nRet == 0)
            nRet = DATA_TIMED_OUT;
    }
 
    return nRet;
}
 
void CSocket::SetBindToDevice( const string& sInterface ) throw(CSocketException)
{
    struct ifreq ifr;
    memset(&ifr, 0, sizeof(ifr));
    snprintf(ifr.ifr_name, sizeof(ifr.ifr_name), sInterface.c_str());
    //Todo:SO_BINDTODEVICE not declared error comes in CygWin, need to compile in Linux.
    /*int nRet = ::setsockopt(m_sockDesc, SOL_SOCKET, SO_BINDTODEVICE, (void*)&ifr, sizeof(ifr));
 
    if (nRet < 0)
    {
        throw CSocketException("Error in binding to device ", true);
    }*/
}
 
UDPSocket::UDPSocket() throw(CSocketException):CSocket(UdpSocket,IPv4Protocol)
{
    SetBroadcast();
}
 
UDPSocket::UDPSocket( unsigned short localPort ) throw(CSocketException):
CSocket(UdpSocket,IPv4Protocol)
{
    BindLocalPort(localPort);
    SetBroadcast();
}
 
UDPSocket::UDPSocket( const string &localAddress, unsigned short localPort ) throw(CSocketException):
CSocket(UdpSocket,IPv4Protocol)
{
    BindLocalAddressAndPort(localAddress, localPort);
    SetBroadcast();
}
 
void UDPSocket::DisconnectFromHost() throw(CSocketException)
{
    sockaddr_in nullAddr;
    memset(&nullAddr, 0, sizeof(nullAddr));
    nullAddr.sin_family = AF_UNSPEC;
    // Try to disconnect
    if (::connect(m_sockDesc, (sockaddr *) &nullAddr, sizeof(nullAddr)) < 0)
    {
        if (errno != EAFNOSUPPORT) 
        {
            throw CSocketException("Disconnect failed (connect())", true);
        }
    }
}
 
void UDPSocket::SendDataGram( const void *buffer, int bufferLen, const string &foreignAddress, 
    unsigned short foreignPort )  throw(CSocketException)
{
    //cout<<"Befor Fill addr";
    sockaddr_in destAddr;
    FillAddr(foreignAddress, foreignPort, destAddr);
    //cout<<"Befor socket send";
    // Write out the whole buffer as a single message.
    if (sendto(m_sockDesc, (void *) buffer, bufferLen, 0,(sockaddr *) &destAddr, sizeof(destAddr)) != bufferLen) 
    {
        throw CSocketException("Send failed (sendto())", true);
    }
 
}
 
int UDPSocket::RecvDataGram( void *buffer, int bufferLen, string &sourceAddress, unsigned short &sourcePort ) 
    throw(CSocketException)
{
    sockaddr_in clntAddr;
    socklen_t addrLen = sizeof(clntAddr);
    int nBytes;
    if ((nBytes = recvfrom(m_sockDesc, (void *) buffer, bufferLen, 0, (sockaddr *) &clntAddr, 
        (socklen_t *) &addrLen)) < 0) 
    {
        throw CSocketException("Receive failed (recvfrom())", true);
    }
    sourceAddress = inet_ntoa(clntAddr.sin_addr);
    sourcePort    = ntohs(clntAddr.sin_port);
    char* sData = static_cast<char *>(buffer);
    sData[nBytes] = '\0';
    return nBytes;
}
 
void UDPSocket::SetMulticastTTL( unsigned char multicastTTL ) throw(CSocketException)
{
    if (setsockopt(m_sockDesc, IPPROTO_IP, IP_MULTICAST_TTL, (void *) &multicastTTL, sizeof(multicastTTL)) < 0) 
    {
        throw CSocketException("Multicast TTL set failed (setsockopt())", true);
    }
}
 
void UDPSocket::JoinGroup( const string &multicastGroup ) throw(CSocketException)
{
    struct ip_mreq multicastRequest;
 
    multicastRequest.imr_multiaddr.s_addr = inet_addr(multicastGroup.c_str());
    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(m_sockDesc, IPPROTO_IP, IP_ADD_MEMBERSHIP, 
        (void *) &multicastRequest, 
        sizeof(multicastRequest)) < 0) 
    {
        throw CSocketException("Multicast group join failed (setsockopt())", true);
    }
 
}
 
void UDPSocket::LeaveGroup( const string &multicastGroup ) throw(CSocketException)
{
    struct ip_mreq multicastRequest;
 
    multicastRequest.imr_multiaddr.s_addr = inet_addr(multicastGroup.c_str());
    multicastRequest.imr_interface.s_addr = htonl(INADDR_ANY);
    if (setsockopt(m_sockDesc, IPPROTO_IP, IP_DROP_MEMBERSHIP, 
        (void *) &multicastRequest, 
        sizeof(multicastRequest)) < 0) 
    {
        throw CSocketException("Multicast group leave failed (setsockopt())", true);
    }
 
}
 
void UDPSocket::SetBroadcast()
{
    // If this fails, we'll hear about it when we try to send.  This will allow 
    // system that cannot broadcast to continue if they don't plan to broadcast
    int broadcastPermission = 1;
    setsockopt(m_sockDesc, SOL_SOCKET, SO_BROADCAST, 
        (void *) &broadcastPermission, sizeof(broadcastPermission));
 
}