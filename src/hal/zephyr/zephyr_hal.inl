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

#include <zephyr/kernel.h>

void tiny_mutex_create(tiny_mutex_t *mutex)
{
    k_mutex_init(mutex);
}

void tiny_mutex_destroy(tiny_mutex_t *mutex)
{
    (void)mutex;
}

void tiny_mutex_lock(tiny_mutex_t *mutex)
{
    (void)k_mutex_lock(mutex, K_FOREVER);
}

uint8_t tiny_mutex_try_lock(tiny_mutex_t *mutex)
{
    return k_mutex_lock(mutex, K_NO_WAIT) == 0;
}

void tiny_mutex_unlock(tiny_mutex_t *mutex)
{
    (void)k_mutex_unlock(mutex);
}

void tiny_events_create(tiny_events_t *events)
{
    k_event_init(events);
}

void tiny_events_destroy(tiny_events_t *events)
{
    (void)events;
}

uint8_t tiny_events_wait(tiny_events_t *events, uint8_t bits, uint8_t clear, uint32_t timeout)
{
    k_timeout_t wait;
    uint32_t matched;

    if ( timeout == 0xFFFFFFFF )
    {
        wait = K_FOREVER;
    }
    else if ( timeout == 0 )
    {
        wait = K_NO_WAIT;
    }
    else
    {
        wait = K_MSEC(timeout);
    }

    matched = k_event_wait(events, bits, false, wait);

    // tinyproto 的 clear 语义是“等到后清除匹配位”，
    // 而 k_event_wait 的 reset 是“等待前清零”，语义不同
    if ( matched != 0 && clear != 0 )
    {
        (void)k_event_clear(events, matched);
    }

    return (uint8_t)matched;
}

uint8_t tiny_events_check_int(tiny_events_t *events, uint8_t bits, uint8_t clear)
{
    return tiny_events_wait(events, bits, clear, 0);
}

void tiny_events_set(tiny_events_t *events, uint8_t bits)
{
    (void)k_event_post(events, bits);
}

void tiny_events_clear(tiny_events_t *events, uint8_t bits)
{
    (void)k_event_clear(events, bits);
}

void tiny_sleep(uint32_t ms)
{
    k_msleep(ms);
}

void tiny_sleep_us(uint32_t us)
{
    k_busy_wait(us);
}

uint32_t tiny_millis(void)
{
    return (uint32_t)k_uptime_get_32();
}

uint32_t tiny_micros(void)
{
    return k_cyc_to_us_floor32(k_cycle_get_32());
}
