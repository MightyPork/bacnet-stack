/**************************************************************************
 *
 * Copyright (C) 2012 Steve Karg <skarg@users.sourceforge.net>
 *
 * Permission is hereby granted, free of charge, to any person obtaining
 * a copy of this software and associated documentation files (the
 * "Software"), to deal in the Software without restriction, including
 * without limitation the rights to use, copy, modify, merge, publish,
 * distribute, sublicense, and/or sell copies of the Software, and to
 * permit persons to whom the Software is furnished to do so, subject to
 * the following conditions:
 *
 * The above copyright notice and this permission notice shall be included
 * in all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
 * EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
 * MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
 * IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
 * CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
 * TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
 * SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *********************************************************************/
#ifndef BACDCODE_H
#define BACDCODE_H

#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include "bacnet/bacnet_stack_exports.h"
#include "bacnet/bacdef.h"
#include "bacnet/datetime.h"
#include "bacnet/bacstr.h"
#include "bacnet/bacint.h"
#include "bacnet/bacreal.h"
#include "bacnet/bits.h"

/**
 * @brief Encode a BACnetARRAY property element; a function template
 * @param object_instance [in] BACnet network port object instance number
 * @param array_index [in] array index requested:
 *    0 to N for individual array members
 * @param apdu [out] Buffer in which the APDU contents are built, or NULL to
 * return the length of buffer if it had been built
 * @return The length of the apdu encoded or
 *   BACNET_STATUS_ERROR for ERROR_CODE_INVALID_ARRAY_INDEX
 */
typedef int (*bacnet_array_property_element_encode_function)(
    uint32_t object_instance, BACNET_ARRAY_INDEX array_index, uint8_t *apdu);

#ifdef __cplusplus
extern "C" {
#endif /* __cplusplus */

/* from clause 20.2.1 General Rules for Encoding BACnet Tags */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int encode_tag(
        uint8_t * apdu,
        uint8_t tag_number,
        bool context_specific,
        uint32_t len_value_type);

BACNET_STACK_EXPORT
bool bacnet_is_opening_tag(uint8_t *apdu, uint32_t apdu_size);
BACNET_STACK_EXPORT
bool bacnet_is_closing_tag(uint8_t *apdu, uint32_t apdu_size);
BACNET_STACK_EXPORT
bool bacnet_is_context_specific(uint8_t *apdu, uint32_t apdu_size);

/* from clause 20.2.1.3.2 Constructed Data */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int encode_opening_tag(
        uint8_t * apdu,
        uint8_t tag_number);
    BACNET_STACK_EXPORT
    int encode_closing_tag(
        uint8_t * apdu,
        uint8_t tag_number);
    BACNET_STACK_EXPORT
    int decode_tag_number(
        uint8_t * apdu,
        uint8_t * tag_number);

    BACNET_STACK_EXPORT
    int bacnet_tag_number_decode(
        uint8_t * apdu,
        uint32_t apdu_len_remaining,
        uint8_t * tag_number);

    BACNET_STACK_EXPORT
    int decode_tag_number_and_value(
        uint8_t * apdu,
        uint8_t * tag_number,
        uint32_t * value);

    BACNET_STACK_EXPORT
    int bacnet_tag_number_and_value_decode(
        uint8_t * apdu,
        uint32_t apdu_len_remaining,
        uint8_t * tag_number,
        uint32_t * value);
/* returns true if the tag is an opening tag and matches */
    BACNET_STACK_EXPORT
    bool decode_is_opening_tag_number(
        uint8_t * apdu,
        uint8_t tag_number);
/* returns true if the tag is a closing tag and matches */
    BACNET_STACK_EXPORT
    bool decode_is_closing_tag_number(
        uint8_t * apdu,
        uint8_t tag_number);
/* returns true if the tag is context specific and matches */
    BACNET_STACK_EXPORT
    bool decode_is_context_tag(
        uint8_t * apdu,
        uint8_t tag_number);
    BACNET_STACK_EXPORT
    bool decode_is_context_tag_with_length(
        uint8_t * apdu,
        uint8_t tag_number,
        int *tag_length);
    /* returns true if the tag is an opening tag */
    BACNET_STACK_EXPORT
    bool decode_is_opening_tag(
        uint8_t * apdu);
    /* returns true if the tag is a closing tag */
    BACNET_STACK_EXPORT
    bool decode_is_closing_tag(
        uint8_t * apdu);

/* from clause 20.2.2 Encoding of a Null Value */
    BACNET_STACK_EXPORT
    int encode_application_null(
        uint8_t * apdu);
    BACNET_STACK_EXPORT
    int encode_context_null(
        uint8_t * apdu,
        uint8_t tag_number);

/* from clause 20.2.3 Encoding of a Boolean Value */
    BACNET_STACK_EXPORT
    int encode_application_boolean(
        uint8_t * apdu,
        bool boolean_value);
    BACNET_STACK_EXPORT
    bool decode_boolean(
        uint32_t len_value);
    BACNET_STACK_EXPORT
    int encode_context_boolean(
        uint8_t * apdu,
        uint8_t tag_number,
        bool boolean_value);
    BACNET_STACK_EXPORT
    bool decode_context_boolean(
        uint8_t * apdu);

    BACNET_STACK_EXPORT
    int decode_context_boolean2(
        uint8_t * apdu,
        uint8_t tag_number,
        bool * boolean_value);

/* from clause 20.2.10 Encoding of a Bit String Value */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int decode_bitstring(
        uint8_t * apdu,
        uint32_t len_value,
        BACNET_BIT_STRING * bit_string);

    BACNET_STACK_EXPORT
    int decode_context_bitstring(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_BIT_STRING * bit_string);
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int encode_bitstring(
        uint8_t * apdu,
        BACNET_BIT_STRING * bit_string);
    BACNET_STACK_EXPORT
    int encode_application_bitstring(
        uint8_t * apdu,
        BACNET_BIT_STRING * bit_string);
    BACNET_STACK_EXPORT
    int encode_context_bitstring(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_BIT_STRING * bit_string);

/* from clause 20.2.6 Encoding of a Real Number Value */
/* and 20.2.1 General Rules for Encoding BACnet Tags */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int encode_application_real(
        uint8_t * apdu,
        float value);
    BACNET_STACK_EXPORT
    int encode_context_real(
        uint8_t * apdu,
        uint8_t tag_number,
        float value);
    BACNET_STACK_EXPORT
    int decode_context_real(
        uint8_t * apdu,
        uint8_t tag_number,
        float *real_value);

/* from clause 20.2.7 Encoding of a Double Precision Real Number Value */
/* and 20.2.1 General Rules for Encoding BACnet Tags */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int encode_application_double(
        uint8_t * apdu,
        double value);

    BACNET_STACK_EXPORT
    int encode_context_double(
        uint8_t * apdu,
        uint8_t tag_number,
        double value);
    BACNET_STACK_EXPORT
    int decode_context_double(
        uint8_t * apdu,
        uint8_t tag_number,
        double *double_value);

/* from clause 20.2.14 Encoding of an Object Identifier Value */
/* and 20.2.1 General Rules for Encoding BACnet Tags */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int decode_object_id(
        uint8_t * apdu,
        BACNET_OBJECT_TYPE * object_type,
        uint32_t * object_instance);
    int decode_object_id_safe(
        uint8_t * apdu,
        uint32_t len_value,
        BACNET_OBJECT_TYPE * object_type,
        uint32_t * object_instance);

    BACNET_STACK_EXPORT
    int bacnet_object_id_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        uint32_t len_value,
        BACNET_OBJECT_TYPE * object_type,
        uint32_t * instance);
    BACNET_STACK_EXPORT
    int bacnet_object_id_application_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        BACNET_OBJECT_TYPE * object_type,
        uint32_t * object_instance);
    BACNET_STACK_EXPORT
    int bacnet_object_id_context_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        uint8_t tag_value,
        BACNET_OBJECT_TYPE * object_type,
        uint32_t * instance);

    BACNET_STACK_EXPORT
    int decode_context_object_id(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_OBJECT_TYPE * object_type,
        uint32_t * instance);

    BACNET_STACK_EXPORT
    int encode_bacnet_object_id(
        uint8_t * apdu,
        BACNET_OBJECT_TYPE object_type,
        uint32_t instance);
    BACNET_STACK_EXPORT
    int encode_context_object_id(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_OBJECT_TYPE object_type,
        uint32_t instance);
    BACNET_STACK_EXPORT
    int encode_application_object_id(
        uint8_t * apdu,
        BACNET_OBJECT_TYPE object_type,
        uint32_t instance);

/* from clause 20.2.8 Encoding of an Octet String Value */
/* and 20.2.1 General Rules for Encoding BACnet Tags */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int encode_octet_string(
        uint8_t * apdu,
        BACNET_OCTET_STRING * octet_string);
    BACNET_STACK_EXPORT
    int encode_application_octet_string(
        uint8_t * apdu,
        BACNET_OCTET_STRING * octet_string);
    BACNET_STACK_EXPORT
    int encode_context_octet_string(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_OCTET_STRING * octet_string);
    BACNET_STACK_EXPORT
    int decode_octet_string(
        uint8_t * apdu,
        uint32_t len_value,
        BACNET_OCTET_STRING * octet_string);
    BACNET_STACK_EXPORT
    int decode_context_octet_string(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_OCTET_STRING * octet_string);

    BACNET_STACK_EXPORT
    int bacnet_octet_string_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        uint32_t len_value,
        BACNET_OCTET_STRING * value);
    BACNET_STACK_EXPORT
    int bacnet_octet_string_application_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        BACNET_OCTET_STRING * value);

/* from clause 20.2.9 Encoding of a Character String Value */
/* and 20.2.1 General Rules for Encoding BACnet Tags */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    uint32_t encode_bacnet_character_string_safe(
        uint8_t * apdu,
        uint32_t max_apdu,
        uint8_t encoding,
        char *pString,
        uint32_t length);
    BACNET_STACK_EXPORT
    int encode_bacnet_character_string(
        uint8_t * apdu,
        BACNET_CHARACTER_STRING * char_string);
    BACNET_STACK_EXPORT
    int encode_application_character_string(
        uint8_t * apdu,
        BACNET_CHARACTER_STRING * char_string);
    BACNET_STACK_EXPORT
    int encode_context_character_string(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_CHARACTER_STRING * char_string);
    BACNET_STACK_EXPORT
    int decode_character_string(
        uint8_t * apdu,
        uint32_t len_value,
        BACNET_CHARACTER_STRING * char_string);
    BACNET_STACK_EXPORT
    int decode_context_character_string(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_CHARACTER_STRING * char_string);
    BACNET_STACK_EXPORT
    int bacnet_character_string_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        uint32_t len_value,
        BACNET_CHARACTER_STRING * char_string);
    BACNET_STACK_EXPORT
    int bacnet_character_string_context_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        uint8_t tag_value,
        BACNET_CHARACTER_STRING * value);


/* from clause 20.2.4 Encoding of an Unsigned Integer Value */
/* and 20.2.1 General Rules for Encoding BACnet Tags */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int encode_bacnet_unsigned(
        uint8_t * apdu,
        BACNET_UNSIGNED_INTEGER value);
    BACNET_STACK_EXPORT
    int encode_context_unsigned(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_UNSIGNED_INTEGER value);
    BACNET_STACK_EXPORT
    int encode_application_unsigned(
        uint8_t * apdu,
        BACNET_UNSIGNED_INTEGER value);
    BACNET_STACK_EXPORT
    int decode_unsigned(
        uint8_t * apdu,
        uint32_t len_value,
        BACNET_UNSIGNED_INTEGER * value);
    BACNET_STACK_EXPORT
    int decode_context_unsigned(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_UNSIGNED_INTEGER * value);

    BACNET_STACK_EXPORT
    int bacnet_unsigned_decode(
        uint8_t * apdu,
        uint16_t apdu_max_len,
        uint32_t len_value,
        BACNET_UNSIGNED_INTEGER * value);
    BACNET_STACK_EXPORT
    int bacnet_unsigned_application_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        BACNET_UNSIGNED_INTEGER * value);
    BACNET_STACK_EXPORT
    int bacnet_unsigned_context_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        uint8_t tag_number,
        BACNET_UNSIGNED_INTEGER * value);

/* from clause 20.2.5 Encoding of a Signed Integer Value */
/* and 20.2.1 General Rules for Encoding BACnet Tags */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int encode_bacnet_signed(
        uint8_t * apdu,
        int32_t value);
    BACNET_STACK_EXPORT
    int encode_application_signed(
        uint8_t * apdu,
        int32_t value);
    BACNET_STACK_EXPORT
    int encode_context_signed(
        uint8_t * apdu,
        uint8_t tag_number,
        int32_t value);
    BACNET_STACK_EXPORT
    int decode_signed(
        uint8_t * apdu,
        uint32_t len_value,
        int32_t * value);
    BACNET_STACK_EXPORT
    int decode_context_signed(
        uint8_t * apdu,
        uint8_t tag_number,
        int32_t * value);

    BACNET_STACK_EXPORT
    int bacnet_signed_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        uint32_t len_value,
        int32_t * value);
    BACNET_STACK_EXPORT
    int bacnet_signed_context_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        uint8_t tag_value,
        int32_t * value);
    BACNET_STACK_EXPORT
    int bacnet_signed_application_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        int32_t * value);

/* from clause 20.2.11 Encoding of an Enumerated Value */
/* and 20.2.1 General Rules for Encoding BACnet Tags */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int bacnet_enumerated_decode(
        uint8_t * apdu,
        uint16_t apdu_max_len,
        uint32_t len_value,
        uint32_t * value);
    BACNET_STACK_EXPORT
    int bacnet_enumerated_context_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        uint8_t tag_value,
        uint32_t * value);
    BACNET_STACK_EXPORT
    int decode_enumerated(
        uint8_t * apdu,
        uint32_t len_value,
        uint32_t * value);
    BACNET_STACK_EXPORT
    int decode_context_enumerated(
        uint8_t * apdu,
        uint8_t tag_value,
        uint32_t * value);
    BACNET_STACK_EXPORT
    int encode_bacnet_enumerated(
        uint8_t * apdu,
        uint32_t value);
    BACNET_STACK_EXPORT
    int encode_application_enumerated(
        uint8_t * apdu,
        uint32_t value);
    BACNET_STACK_EXPORT
    int encode_context_enumerated(
        uint8_t * apdu,
        uint8_t tag_number,
        uint32_t value);

/* from clause 20.2.13 Encoding of a Time Value */
/* and 20.2.1 General Rules for Encoding BACnet Tags */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int encode_bacnet_time(
        uint8_t * apdu,
        BACNET_TIME * btime);
    BACNET_STACK_EXPORT
    int encode_application_time(
        uint8_t * apdu,
        BACNET_TIME * btime);
    BACNET_STACK_EXPORT
    int decode_bacnet_time(
        uint8_t * apdu,
        BACNET_TIME * btime);
    BACNET_STACK_EXPORT
    int decode_bacnet_time_safe(
        uint8_t * apdu,
        uint32_t len_value,
        BACNET_TIME * btime);
    BACNET_STACK_EXPORT
    int encode_context_time(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_TIME * btime);
    BACNET_STACK_EXPORT
    int decode_application_time(
        uint8_t * apdu,
        BACNET_TIME * btime);
    BACNET_STACK_EXPORT
    int decode_context_bacnet_time(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_TIME * btime);

    BACNET_STACK_EXPORT
    int bacnet_time_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        uint32_t len_value,
        BACNET_TIME * value);
    BACNET_STACK_EXPORT
    int bacnet_time_context_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        uint8_t tag_value,
        BACNET_TIME * value);
    BACNET_STACK_EXPORT
    int bacnet_time_application_decode(
        uint8_t * apdu,
        uint16_t apdu_len_max,
        BACNET_TIME * value);

/* BACnet Date */
/* year = years since 1900 */
/* month 1=Jan */
/* day = day of month */
/* wday 1=Monday...7=Sunday */

/* from clause 20.2.12 Encoding of a Date Value */
/* and 20.2.1 General Rules for Encoding BACnet Tags */
/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int encode_bacnet_date(
        uint8_t * apdu,
        BACNET_DATE * bdate);
    BACNET_STACK_EXPORT
    int encode_application_date(
        uint8_t * apdu,
        BACNET_DATE * bdate);
    BACNET_STACK_EXPORT
    int encode_context_date(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_DATE * bdate);
    BACNET_STACK_EXPORT
    int decode_date(
        uint8_t * apdu,
        BACNET_DATE * bdate);
    BACNET_STACK_EXPORT
    int decode_date_safe(
        uint8_t * apdu,
        uint32_t len_value,
        BACNET_DATE * bdate);
    BACNET_STACK_EXPORT
    int decode_application_date(
        uint8_t * apdu,
        BACNET_DATE * bdate);
    BACNET_STACK_EXPORT
    int decode_context_date(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_DATE * bdate);

/* from clause 20.1.2.4 max-segments-accepted */
/* and clause 20.1.2.5 max-APDU-length-accepted */
/* returns the encoded octet */
    BACNET_STACK_EXPORT
    uint8_t encode_max_segs_max_apdu(
        int max_segs,
        int max_apdu);
    BACNET_STACK_EXPORT
    int decode_max_segs(
        uint8_t octet);
    BACNET_STACK_EXPORT
    int decode_max_apdu(
        uint8_t octet);

/* returns the number of apdu bytes consumed */
    BACNET_STACK_EXPORT
    int encode_simple_ack(
        uint8_t * apdu,
        uint8_t invoke_id,
        uint8_t service_choice);

    BACNET_STACK_EXPORT
    int encode_bacnet_address(
        uint8_t * apdu,
        BACNET_ADDRESS * destination);
    BACNET_STACK_EXPORT
    int decode_bacnet_address(
        uint8_t * apdu,
        BACNET_ADDRESS * destination);
    BACNET_STACK_EXPORT
    int encode_context_bacnet_address(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_ADDRESS * destination);
    BACNET_STACK_EXPORT
    int decode_context_bacnet_address(
        uint8_t * apdu,
        uint8_t tag_number,
        BACNET_ADDRESS * destination);

    BACNET_STACK_EXPORT
    int bacnet_array_encode(
        uint32_t object_instance,
        BACNET_ARRAY_INDEX array_index,
        bacnet_array_property_element_encode_function encoder,
        BACNET_UNSIGNED_INTEGER array_size,
        uint8_t *apdu,
        int max_apdu);

/* from clause 20.2.1.2 Tag Number */
/* true if extended tag numbering is used */
#define IS_EXTENDED_TAG_NUMBER(x) (((x) & 0xF0) == 0xF0)

/* from clause 20.2.1.3.1 Primitive Data */
/* true if the extended value is used */
#define IS_EXTENDED_VALUE(x) (((x) & 0x07) == 5)

/* from clause 20.2.1.1 Class */
/* true if the tag is context specific */
#define IS_CONTEXT_SPECIFIC(x) (((x) & BIT(3)) == BIT(3))

/* from clause 20.2.1.3.2 Constructed Data */
/* true if the tag is an opening tag */
#define IS_OPENING_TAG(x) (((x) & 0x07) == 6)

/* from clause 20.2.1.3.2 Constructed Data */
/* true if the tag is a closing tag */
#define IS_CLOSING_TAG(x) (((x) & 0x07) == 7)

#ifdef __cplusplus
}
#endif /* __cplusplus */
#endif
