
#ifndef __SYSTEM_TYPE_DEFINES_H__
#define __SYSTEM_TYPE_DEFINES_H__

#pragma region data type
typedef long long SI64;
typedef unsigned int UI32;
typedef unsigned long long UI64;
typedef int SI32;
typedef unsigned short UI16;
typedef short SI16;
#pragma endregion

#pragma region Log about
enum ELogLevelType
{
	ELLT_NONE = 0,		//	无
	ELLT_ECHO,			//	普通
	ELLT_DEBUG,			//	调试（此级别及以下，非DEBUG模式不做文件打印）
	ELLT_MSG,			//	信息
	ELLT_WARNING,		//	警告
	ELLT_ERROR,			//	错误

	ELLT_MAX
};

#pragma endregion

#pragma region File check permission

enum EFilePermissionCheckResult
{
	EFPCR_SUCCESS = 0,			//	有该权限
	EFPCR_NO_PERMISSION			//	没有该权限
};

enum EFileCheckSystemType
{
	EFCST_EXISTS = 0,			//	查看文件是否存在
	EFCST_WRITE = 2,			//	当前用户是否有写权限
	EFCST_READ = 4,				//	当前用户是否有读权限
	EFCST_READ_WRITE = 6		//	当前用户是否有读写权限
};

enum EFileCheckType
{
	EFCT_NONE = 0,
	EFCT_EXITS = 1,
	EFCT_WRITE = 2,
	EFCT_READ = 4,
};

enum EFileDeleteErrorType
{
	EFDET_SUCCESS = 0,			//	删除文件成功
	EFDET_EROFS,				//	文件为只读权限
	EFDET_EFAULT,				//	文件名称指针超出可读取内存空间
	EFDET_ENAMETOOLONG,			//	文件名超长
	EFDET_ENOMEN,				//	内存不足
	EFDET_ELOOP,				//	文件有过多的符号连接
	EFDET_EIO,					//	IO错误

	EFDET_MAX
};

#pragma endregion

#endif	//	__SYSTEM_TYPE_DEFINES_H__
