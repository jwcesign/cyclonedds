/*
 * Copyright(c) 2006 to 2018 ADLINK Technology Limited and others
 *
 * This program and the accompanying materials are made available under the
 * terms of the Eclipse Public License v. 2.0 which is available at
 * http://www.eclipse.org/legal/epl-2.0, or the Eclipse Distribution License
 * v. 1.0 which is available at
 * http://www.eclipse.org/org/documents/edl-v10.php.
 *
 * SPDX-License-Identifier: EPL-2.0 OR BSD-3-Clause
 */
#include <criterion/criterion.h>
#include <criterion/logging.h>
#include "ddsc/dds.h"
#include "TypesArrayKey.h"


#define strfy(s) #s
#define DDSC_ARRAYTYPEKEY_TEST(type, init) \
    do { \
        dds_return_t status; \
        dds_entity_t par, top, wri; \
        TypesArrayKey_##type##_arraytypekey data; \
        for( unsigned i = 0; i < (sizeof data.key / sizeof *data.key); i++) data.key[i] = (init); \
        \
        par = dds_create_participant(DDS_DOMAIN_DEFAULT, NULL, NULL); \
        cr_assert_gt(par, 0); \
        top = dds_create_topic(par, &TypesArrayKey_##type##_arraytypekey_desc, strfy(type), NULL, NULL); \
        cr_assert_gt(top, 0); \
        wri = dds_create_writer(par, top, NULL, NULL); \
        cr_assert_gt(wri, 0); \
        \
        status = dds_write(wri, &data); \
        cr_assert_eq(dds_err_nr(status), DDS_RETCODE_OK); \
        \
        dds_delete(wri); \
        dds_delete(top); \
        dds_delete(par); \
    } while (0)


Test(ddsc_types, long_arraytypekey)
{
    DDSC_ARRAYTYPEKEY_TEST(long, 1);
}

Test(ddsc_types, longlong_arraytypekey)
{
    DDSC_ARRAYTYPEKEY_TEST(longlong, 1);
}

Test(ddsc_types, unsignedshort_arraytypekey)
{
    DDSC_ARRAYTYPEKEY_TEST(unsignedshort, 1);
}

Test(ddsc_types, unsignedlong_arraytypekey)
{
    DDSC_ARRAYTYPEKEY_TEST(unsignedlong, 1);
}

Test(ddsc_types, unsignedlonglong_arraytypekey)
{
    DDSC_ARRAYTYPEKEY_TEST(unsignedlonglong, 1);
}

Test(ddsc_types, float_arraytypekey)
{
    DDSC_ARRAYTYPEKEY_TEST(float, 1.0f);
}

Test(ddsc_types, double_arraytypekey)
{
    DDSC_ARRAYTYPEKEY_TEST(double, 1.0f);
}

Test(ddsc_types, char_arraytypekey)
{
    DDSC_ARRAYTYPEKEY_TEST(char, '1');
}

Test(ddsc_types, boolean_arraytypekey)
{
    DDSC_ARRAYTYPEKEY_TEST(boolean, true);
}

Test(ddsc_types, octet_arraytypekey)
{
    DDSC_ARRAYTYPEKEY_TEST(octet, 1);
}

Test(ddsc_types, alltypeskey)
{
    dds_return_t status;
    dds_entity_t par, top, wri;
    const TypesArrayKey_alltypeskey atk_data = {
        .l = -1,
        .ll = -1,
        .us = 1,
        .ul = 1,
        .ull = 1,
        .f = 1.0f,
        .d = 1.0f,
        .c = '1',
        .b = true,
        .o = 1,
        .s = "1"
    };

    par = dds_create_participant(DDS_DOMAIN_DEFAULT, NULL, NULL);
    cr_assert_gt(par, 0);
    top = dds_create_topic(par, &TypesArrayKey_alltypeskey_desc, "AllTypesKey", NULL, NULL);
    cr_assert_gt(top, 0);
    wri = dds_create_writer(par, top, NULL, NULL);
    cr_assert_gt(wri, 0);

    status = dds_write(wri, &atk_data);
    cr_assert_eq(dds_err_nr(status), DDS_RETCODE_OK);

    dds_delete(wri);
    dds_delete(top);
    dds_delete(par);
}
