/*
    Copyright 2026 (C) caodd

    This file is part of Tiny Protocol Library.

    GNU General Public License Usage

    Protocol Library is free software: you can redistribute it and/or modify
    it under the terms of the GNU Lesser General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    Protocol Library is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU Lesser General Public License for more details.

    You should have received a copy of the GNU Lesser General Public License
    along with Protocol Library.  If not, see <http://www.gnu.org/licenses/>.
*/

#pragma once

#include <zephyr/kernel.h>
#include <stdint.h>

/* For fastest version of protocol assign all defines to zero.
 * In this case protocol supports no CRC field, and
 * all api functions become not thread-safe.
 */

#ifndef CONFIG_ENABLE_CHECKSUM
#define CONFIG_ENABLE_CHECKSUM
#endif

#ifndef CONFIG_ENABLE_FCS16
#define CONFIG_ENABLE_FCS16
#endif

#ifndef CONFIG_ENABLE_FCS32
#define CONFIG_ENABLE_FCS32
#endif

// Zephyr 内核对象承担互斥锁与事件组
#define CONFIG_TINYHAL_THREAD_SUPPORT 1

/**
 * Mutex type used by Tiny Protocol implementation.
 */
typedef struct k_mutex tiny_mutex_t;

/**
 * Events group type used by Tiny Protocol implementation.
 */
typedef struct k_event tiny_events_t;
