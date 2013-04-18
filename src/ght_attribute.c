/******************************************************************************
*  LibGHT, software to manage point clouds.
*  LibGHT is free and open source software provided by the Government of Canada
*  Copyright (c) 2012 Natural Resources Canada
*
*  Nouri Sabo <nsabo@NRCan.gc.ca>, Natural Resources Canada
*  Paul Ramsey <pramsey@opengeo.org>, OpenGeo
*
******************************************************************************/

#include "ght_internal.h"
#include <strings.h>

GhtErr ght_type_size(GhtType type, size_t *size)
{
    assert(size);
    assert(type);
    *size = GhtTypeSizes[type];
    return GHT_OK;
}

GhtErr ght_type_from_str(const char *str, GhtType *type)
{
    int i;
    for ( i = 0; i < GHT_NUM_TYPES; i++ )
    {
        if ( strcasecmp(str, GhtTypeStrings[i]) == 0 )
        {
            *type = i;
            return GHT_OK;
        }
    }
    return GHT_ERROR;
}


/******************************************************************************/
/* GhtAttribute */

GhtErr ght_attribute_new(const GhtDimension *dim, double val, GhtAttribute **attr)
{
    GhtAttribute *a;
    a = ght_malloc(sizeof(GhtAttribute));
    if ( ! a ) return GHT_ERROR;
    memset(a, 0, sizeof(GhtAttribute));
    a->dim = dim;
    a->next = NULL;
    GHT_TRY(ght_attribute_set_value(a, val));
    *attr = a;
    return GHT_OK;
}

GhtErr
ght_attribute_free(GhtAttribute *attr)
{
    if ( attr->next )
    {
        ght_attribute_free(attr->next);
    }
    ght_free(attr);
    return GHT_OK;
}

GhtErr
ght_attribute_get_by_dimension(const GhtAttribute *attr, const GhtDimension *dim, GhtAttribute *found)
{
    if ( ! attr ) return GHT_ERROR;
    while ( attr->dim != dim )
    {
        if ( ! attr->next ) return GHT_ERROR;
        attr = attr->next;
    }
    memcpy(found, attr, sizeof(GhtAttribute));
    return GHT_OK;
}

/** Convert a real value double into a value suitable for storage */
static GhtErr
ght_attribute_double_to_storage(const GhtDimension *dim, double *val)
{
    if ( dim->offset )
    {
        *val -= dim->offset;
    }
    if ( dim->scale != 1 )
    {
        *val /= dim->scale;
    }
    return GHT_OK;
}

/** Convert a real value double into a value suitable for storage */
static GhtErr
ght_attribute_storage_to_double(const GhtDimension *dim, double *val)
{
    if ( dim->scale != 1 )
    {
        *val *= dim->scale;
    }
    if ( dim->offset )
    {
        *val += dim->offset;
    }
    return GHT_OK;
}

GhtErr ght_attribute_get_value(const GhtAttribute *attr, double *val)
{
    const GhtType type = attr->dim->type;
    size_t size = GhtTypeSizes[type];
    switch(type)
    {
        case GHT_UNKNOWN:
        {
            ght_error("%s: unknown attribute type", __func__);
            return GHT_ERROR;
        }
        case GHT_INT8:
        {
            int8_t v;
            memcpy(&v, attr->val, size);
            *val = v;
            break;
        }
        case GHT_UINT8:
        {
            uint8_t v;
            memcpy(&v, attr->val, size);
            *val = v;
            break;
        }
        case GHT_INT16:
        {
            int16_t v;
            memcpy(&v, attr->val, size);
            *val = v;
            break;
        }
        case GHT_UINT16:
        {
            uint16_t v;
            memcpy(&v, attr->val, size);
            *val = v;
            break;
        }
        case GHT_INT32:
        {
            int32_t v;
            memcpy(&v, attr->val, size);
            *val = v;
            break;
        }
        case GHT_UINT32:
        {
            uint32_t v;
            memcpy(&v, attr->val, size);
            *val = v;
            break;
        }
        case GHT_INT64:
        {
            int64_t v;
            memcpy(&v, attr->val, size);
            *val = v;
            break;
        }
        case GHT_UINT64:
        {
            uint64_t v;
            memcpy(&v, attr->val, size);
            *val = v;
            break;
        }
        case GHT_DOUBLE:
        {
            double v;
            memcpy(&v, attr->val, size);
            *val = v;
            break;
        }
        case GHT_FLOAT:
        {
            float v;
            memcpy(&v, attr->val, size);
            *val = v;
            break;
        }
        default:
        {
            ght_error("%s: unknown attribute type %d", __func__, type);
            return GHT_ERROR;
        }
    }
    GHT_TRY(ght_attribute_storage_to_double(attr->dim, val));
    return GHT_OK;    
}


GhtErr ght_attribute_set_value(GhtAttribute *attr, double val)
{
    const GhtType type = attr->dim->type;
    size_t size = GhtTypeSizes[type];
    double dv = val;
    
    GHT_TRY(ght_attribute_double_to_storage(attr->dim, &dv));
    
    switch(type)
    {
        case GHT_UNKNOWN:
        {
            ght_error("%s: unknown attribute type %d", __func__, type);
            return GHT_ERROR;
        }
        case GHT_INT8:
        {
            int8_t v = dv;
            memcpy(attr->val, &v, size);
            return GHT_OK;
        }
        case GHT_UINT8:
        {
            uint8_t v = dv;
            memcpy(attr->val, &v, size);
            return GHT_OK;
        }
        case GHT_INT16:
        {
            int16_t v = dv;
            memcpy(attr->val, &v, size);
            return GHT_OK;
        }
        case GHT_UINT16:
        {
            uint16_t v = dv;
            memcpy(attr->val, &v, size);
            return GHT_OK;
        }
        case GHT_INT32:
        {
            int32_t v = dv;
            memcpy(attr->val, &v, size);
            return GHT_OK;
        }
        case GHT_UINT32:
        {
            uint32_t v = dv;
            memcpy(attr->val, &v, size);
            return GHT_OK;
        }
        case GHT_INT64:
        {
            int64_t v = dv;
            memcpy(attr->val, &v, size);
            return GHT_OK;
        }
        case GHT_UINT64:
        {
            uint64_t v = dv;
            memcpy(attr->val, &v, size);
            return GHT_OK;
        }
        case GHT_DOUBLE:
        {
            double v = dv;
            memcpy(attr->val, &v, size);
            return GHT_OK;
        }
        case GHT_FLOAT:
        {
            float v = dv;
            memcpy(attr->val, &v, size);
            return GHT_OK;
        }
        default:
        {
            ght_error("%s: unknown attribute type %d", __func__, type);
            return GHT_ERROR;
        }
    }
    return GHT_OK;
}

GhtErr ght_attribute_to_string(const GhtAttribute *attr, stringbuffer_t *sb)
{
    double d;
    GHT_TRY(ght_attribute_get_value(attr, &d));
    stringbuffer_aprintf(sb, "%s=%g", attr->dim->name, d);
    return GHT_OK;
}






