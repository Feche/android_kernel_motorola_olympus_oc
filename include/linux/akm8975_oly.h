/*
 * Copyright 2013: Olympus Kernel Project
 * <http://forum.xda-developers.com/showthread.php?t=2016837>
 
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.

 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

/*
 * Definitions for akm8975 compass chip.
 */
#ifndef AKM8975_H
#define AKM8975_H

#include <linux/ioctl.h>

/*! \name AK8975 operation mode
 \anchor AK8975_Mode
 Defines an operation mode of the AK8975.*/
/*! @{*/
#define AK8975_MODE_SNG_MEASURE   0x01
#define	AK8975_MODE_SELF_TEST     0x08
#define	AK8975_MODE_FUSE_ACCESS   0x0F
#define	AK8975_MODE_POWER_DOWN    0x00
/*! @}*/

#define RBUFF_SIZE		8	/* Rx buffer size */ /* Original from Olympus driver*/

/*! \name AK8975 register address
\anchor AK8975_REG
Defines a register address of the AK8975.*/
/*! @{*/
#define AK8975_REG_WIA		0x00
#define AK8975_REG_INFO		0x01
#define AK8975_REG_ST1		0x02
#define AK8975_REG_HXL		0x03
#define AK8975_REG_HXH		0x04
#define AK8975_REG_HYL		0x05
#define AK8975_REG_HYH		0x06
#define AK8975_REG_HZL		0x07
#define AK8975_REG_HZH		0x08
#define AK8975_REG_ST2		0x09
#define AK8975_REG_CNTL		0x0A
#define AK8975_REG_RSV		0x0B
#define AK8975_REG_ASTC		0x0C
#define AK8975_REG_TS1		0x0D
#define AK8975_REG_TS2		0x0E
#define AK8975_REG_I2CDIS	0x0F
/*! @}*/

/*! \name AK8975 fuse-rom address
\anchor AK8975_FUSE
Defines a read-only address of the fuse ROM of the AK8975.*/
/*! @{*/
#define AK8975_FUSE_ASAX	0x10
#define AK8975_FUSE_ASAY	0x11
#define AK8975_FUSE_ASAZ	0x12
/*! @}*/

#define AKMIO                   0xA1

/* IOCTLs for AKM library */
#define ECS_IOCTL_WRITE             _IOW(AKMIO, 0x02, char[5])	/* Original ECS from Olympus driver*/
#define ECS_IOCTL_READ              _IOWR(AKMIO, 0x03, char[5])	/* Original ECS from Olympus driver*/
#define ECS_IOCTL_GETDATA           _IOR(AKMIO, 0x08, char[RBUFF_SIZE])	/* Original ECS from Olympus driver*/
#define ECS_IOCTL_SET_YPR           _IOW(AKMIO, 0x0C, short[12])	/* Original ECS from Olympus driver*/
#define ECS_IOCTL_GET_OPEN_STATUS   _IOR(AKMIO, 0x0D, int)	/* Original ECS from Olympus driver*/
#define ECS_IOCTL_GET_CLOSE_STATUS  _IOR(AKMIO, 0x0E, int)	/* Original ECS from Olympus driver*/
#define ECS_IOCTL_GET_DELAY         _IOR(AKMIO, 0x30, short)	/* Original ECS from Olympus driver*/

/* IOCTLs for APPs */
#define ECS_IOCTL_APP_SET_MFLAG		_IOW(AKMIO, 0x11, short)	/* Original ECS from Olympus driver*/
#define ECS_IOCTL_APP_GET_MFLAG		_IOW(AKMIO, 0x12, short)	/* Original ECS from Olympus driver*/
#define ECS_IOCTL_APP_SET_AFLAG		_IOW(AKMIO, 0x13, short)	/* Original ECS from Olympus driver*/
#define ECS_IOCTL_APP_GET_AFLAG		_IOR(AKMIO, 0x14, short)	/* Original ECS from Olympus driver*/
#define ECS_IOCTL_APP_SET_DELAY		_IOW(AKMIO, 0x18, short)	/* Original ECS from Olympus driver*/
#define ECS_IOCTL_APP_GET_DELAY		ECS_IOCTL_GET_DELAY		/* Original ECS from Olympus driver*/
/* Set raw magnetic vector flag */
#define ECS_IOCTL_APP_SET_MVFLAG	_IOW(AKMIO, 0x19, short)	/* Original ECS from Olympus driver*/
/* Get raw magnetic vector flag */
#define ECS_IOCTL_APP_GET_MVFLAG	_IOR(AKMIO, 0x1A, short)	/* Original ECS from Olympus driver*/
#define ECS_IOCTL_APP_SET_TFLAG         _IOR(AKMIO, 0x15, short)	/* Original ECS from Olympus driver*/

struct akm8975_platform_data {
	int intr;

	int (*init)(void);
	void (*exit)(void);
	int (*power_on)(void);
	int (*power_off)(void);
};

#endif
