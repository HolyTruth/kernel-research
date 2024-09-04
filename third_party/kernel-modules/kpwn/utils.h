/* SPDX-License-Identifier: GPL-2.0 */
/* Copyright 2024 Google LLC
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 * GNU General Public License for more details.
*/

#pragma once

#define LOG(msg, ...) printk(KERN_ERR "kpwn: " msg "\n" __VA_OPT__(,) __VA_ARGS__)

#define CHECK_ALLOC(x) ({ \
    typeof(x) __temp = (x); \
    if(!__temp) { \
        LOG("%s: " #x " returned 0.", __func__); \
        return -ERROR_ALLOC; \
    } \
    __temp; \
})

#define CHECK_ZERO_NO_RET(x) ({ \
    typeof(x) __temp = (x); \
    if(__temp) \
        LOG("%s: " #x " returned non-zero (%ld).", __func__, (long int) __temp); \
    __temp; \
})

#define CHECK_ZERO(x, ERROR_CODE) ({ \
    typeof(x) __temp = (x); \
    if(__temp) { \
        LOG("%s: " #x " returned non-zero.", __func__); \
        return -ERROR_CODE; \
    } \
    __temp; \
})

#define STRUCT_FROM_USER(kernel_struct_ptr, user_ptr) CHECK_ZERO(copy_from_user(kernel_struct_ptr, user_ptr, sizeof(*kernel_struct_ptr)), ERROR_COPY_FROM_USER_STRUCT)
#define STRUCT_TO_USER(kernel_struct_ptr, user_ptr) CHECK_ZERO(copy_to_user(user_ptr, kernel_struct_ptr, sizeof(*kernel_struct_ptr)), ERROR_COPY_TO_USER_STRUCT)
#define DATA_FROM_USER(kernel_ptr, user_ptr, len) CHECK_ZERO(raw_copy_from_user(kernel_ptr, user_ptr, len), ERROR_COPY_FROM_USER_DATA)
#define DATA_TO_USER(kernel_ptr, user_ptr, len) CHECK_ZERO(raw_copy_to_user(user_ptr, kernel_ptr, len), ERROR_COPY_TO_USER_DATA);
#define STRING_FROM_USER(kernel_buf, user_ptr) CHECK_ALLOC(strncpy_from_user(kernel_buf, user_ptr, ARRAY_SIZE(kernel_buf)))
