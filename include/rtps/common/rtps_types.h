/******************************************************************************
 *   Copyright (C) 2017 Edward Scott. All rights reserved.
 *   Authors: Edward Scott <eddy.scott88@gmail.com>
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 * 3. Neither the name Tiny RTPS nor the names of its contributors may be
 *    used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS
 * OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN
 * ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 * POSSIBILITY OF SUCH DAMAGE.
 *
 ***************************************************************************/
#ifndef TINY_RTPS_RTPS_TYPES_H
#define TINY_RTPS_RTPS_TYPES_H

#ifdef __cplusplus
extern "C"{
#endif

#include "platform_types.h"
#include "guid.h"

/**
 * @defgroup RTPS_TYPES Types that appear within submessages or built-in topic
 * data.  Most descriptions pulled directly from the RTPS specification
 * @{
 */

/**
 * @brief Type used to hold a timestamp. Should have at least nano-second
 * resolution.
 * The representation of the time is the one defined by the IETF Network Time Protocol (NTP)
 * Standard (IETF RFC 1305). In this representation, time is expressed in seconds and fraction
 * of seconds using the formula:
 */
typedef struct Time_t {
  long seconds; // time in seconds
  unsigned long fraction; // time in sec/2^32
} Time_t;

// reserved time values:
#define TIME_ZERO {0, 0}
#define TIME_INVALID {-1, 0xffffffff}
#define TIME_INFINITE {0x7fffffff, 0xffffffff}

#define SIZE_VENDOR_ID 2
/**
 * @brief The vendorId identifies the vendor of the middleware that implemented
 * the RTPS protocol and allows this vendor to add specific extensions to the
 * protocol.
 */
typedef struct VendorId_t {
  octet vendorId[SIZE_VENDOR_ID];
} VendorId_t;

// Reserved vendor ID and current vendor IDs
#define VENDORID_UNKNOWN {0,0}
// TODO vendor ids of known implementations

/**
 * @brief Type used to hold sequence numbers. Must be possible to represent
 * using 64 bits.
 *
 * sequence number type contains bytes which map to a value
 * seq_num = high * 2^32 + low
 */
typedef struct SequenceNumber_t {
  long high;
  unsigned long low;
} SequenceNumber_t;
#define SEQUENCE_NUMBER_UNKNOWN {-1,0}

/**
 * @brief A fragment number is a 32-bit unsigned integer and is used by
 * Submessages to identify a particular fragment in fragmented serialized data.
 */
typedef struct FragmentNumber_t {
  unsigned long value;
} FragmentNumber_t;


#define SIZE_LOCATOR_ADDRESS 16
/**
 * @brief Used to give the port and address of the underlying transport layer,
 *        which is stored in the kind field
 *
 * If the Locator_t kind is LOCATOR_KIND_UDPv4, the address contains an IPv4
 * address. In this case the leading 12 octets of the address must be zero. The
 * last 4 octets are used to store the IPv4 address. The mapping between the
 * dot-notation “a.b.c.d” of an IPv4 address and its representation in the
 * address field of a Locator_t is:
 * address = (0,0,0,0,0,0,0,0,0,0,0,0,a,b,c,d}
 * If the Locator_t kind is LOCATOR_KIND_UDPv6, the address contains an IPv6
 * address. IPv6 addresses typically use a shorthand hexadecimal notation that
 * maps one-to-one to the 16 octets in the address field.
 * For example the representation of the IPv6 address “FF00:4501:0:0:0:0:0:32” is:
 * address = (0xff,0,0x45,0x01,0,0,0,0,0,0,0,0,0,0,0,0x32}
 */
typedef struct Locator_t {
  long kind;
  unsigned long port;
  octet address[SIZE_LOCATOR_ADDRESS];
} Locator_t;

#define LOCATOR_KIND_INVALID -1
#define LOCATOR_ADDRESS_INVALID {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
#define LOCATOR_PORT_INVALID 0
#define LOCATOR_KIND_RESERVED 0
#define LOCATOR_KIND_UDPv4 1
#define LOCATOR_KIND_UDPv6 2
#define LOCATOR_INVALID \
{LOCATOR_KIND_INVALID, LOCATOR_PORT_INVALID, LOCATOR_ADDRESS_INVALID}

/**
 * @brief Used in addition to the DDS specification to distiguish whether or
 * not the topic has defined some fields within to be used as the 'Key' that
 * identifies data-instances within the topic
 */
typedef struct TopicKind_t {
  long value;
} TopicKind_t;
#define TOPIC_KIND_NO_KEY 1
#define TOPIC_KIND_WITH_KEY 2

/**
 * @brief Enumeration used to indicate the level of the reliability used for communications.
 * It can take the values:
 * BEST_EFFORT, RELIABLE.
 */
typedef struct ReliabilityKind_t {
  long value;
} ReliabilityKind_t;
#define RELIABILITY_KIND_BEST_EFFORT 1
#define RELIABILITY_KIND_RELIABLE 3

/**
 * @brief Type used to encapsulate a count that is incremented monotonically,
 * used to identify message duplicates.
 */
typedef struct Count_t {
  long value;
} Count_t;

/**
 * @brief Type used to represent the version of the RTPS protocol. The version
 * is composed of a major and a minor version number.
 */
typedef struct ProtocolVersion_t {
  octet major;
  octet minor;
} ProtocolVersion_t;
#define PROTOCOLVERSION_1_0 {1,0}
#define PROTOCOLVERSION_1_1 {1,1}
#define PROTOCOLVERSION_2_0 {2,0}
#define PROTOCOLVERSION_2_1 {2,1}
#define PROTOCOLVERSION_2_2 {2,2}
#define PROTOCOLVERSION PROTOCOLVERSION_2_2


#define SIZE_KEY_HASH_VALUE 16
/**
 * @brief The Key Hash provides a hint for the key that uniquely identifies the
 * data-object that is being changed within the set of objects that have been
 * registered by the DDS DataWriter
 */
typedef struct KeyHash_t {
  octet value[SIZE_KEY_HASH_VALUE];
} KeyHash_t;

#define SIZE_STATUS_INFO_VALUE 4
/**
 * @breif //TODO PID_STATUS_INFO, RTPS spec not specific about what this is
 */
typedef struct StatusInfo_t {
  octet value[SIZE_STATUS_INFO_VALUE];
} StatusInfo_t;

/**
 * @brief Type used to uniquely identify a parameter in a parameter list.
 * Used extensively by the Discovery Module mainly to define QoS Parameters.
 * A range of values is reserved for protocol-defined parameters, while another
 * range can be used for vendor-defined parameters
 */
typedef struct ParameterId_t {
  short value;
} ParameterId_t;

#define SIZE_CONTENT_FILTER_STRING 256
/**
 * @brief The ContentFilterProperty_t field provides all the required
 * information to enable content filtering on the Writer side.
 */
typedef struct ContentFilterProperty_t {
  octet contentFilteredTopicName[SIZE_CONTENT_FILTER_STRING];
  octet relatedTopicName[SIZE_CONTENT_FILTER_STRING];
  octet filterClassName[SIZE_CONTENT_FILTER_STRING];
  RtpsString_t *expressionParameters; //TODO Eddy 2017, this is a string table, how best to handle this in C
  RtpsString_t filterExpression;
} ContentFilterProperty_t;


#define SIZE_FILTER_SIGNATURE_RESULT 4
/**
 * @brief The inline Qos element of the Data submessage is used to include the
 * necessary filter information, this is added via adding a ContentFilterInfo_t
 */
typedef struct ContentFilterInfo_t {
  long * filterResult;
  size_t size_filter_result_array;
  long* filterSignatures; // Array of long[SIZE_FILTER_SIGNATURE_RESULT]
  size_t size_filter_signatures_array;
} ContentFilterInfo_t;

/**
 * @brief //TODO Eddy 8/2017, the spec documentation on this type is lacking
 */
typedef struct Property_t {
  RtpsString_t name;
  RtpsString_t value;
} Property_t;

/**
 * @brief A string used to give a given RTPS entity a human readable name
 */
typedef struct EntityName_t {
  RtpsString_t name;
} EntityName_t;

/**
 * @breif structure to hold information about a specific parameter
 */
typedef struct Parameter_t {
  ParameterId_t parameterId;
  short length;
  octet value[];
} Parameter_t;

/**
 * @breif A list of parameters, this is used in several messages such as
 *        OriginalWriterInfo_t
 */
typedef struct ParameterList_t{
  size_t size_of_parameter_list;
  Parameter_t* parameter;
}ParameterList_t;

/**
 * @breif Data about the original writer of the RTPS message
 */
typedef struct OriginalWriterInfo_t {
  GUID_t originalWriterGUID;
  SequenceNumber_t originalWriterSN;
  ParameterList_t originalWriterQos;
} OriginalWriterInfo_t;

typedef unsigned long BuiltinEndpointSet_t;
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_ANNOUNCER 0x00000001 << 0;
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_DETECTOR 0x00000001 << 1;
#define DISC_BUILTIN_ENDPOINT_PUBLICATION_ANNOUNCER 0x00000001 << 2;
#define DISC_BUILTIN_ENDPOINT_PUBLICATION_DETECTOR 0x00000001 << 3;
#define DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_ANNOUNCER 0x00000001 << 4;
#define DISC_BUILTIN_ENDPOINT_SUBSCRIPTION_DETECTOR 0x00000001 << 5;
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_PROXY_ANNOUNCER 0x00000001 << 6;
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_PROXY_DETECTOR 0x00000001 << 7;
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_STATE_ANNOUNCER 0x00000001 << 8;
#define DISC_BUILTIN_ENDPOINT_PARTICIPANT_STATE_DETECTOR 0x00000001 << 9;
#define BUILTIN_ENDPOINT_PARTICIPANT_MESSAGE_DATA_WRITER 0x00000001 << 10;
#define BUILTIN_ENDPOINT_PARTICIPANT_MESSAGE_DATA_READER 0x00000001 << 11;

/**
 * @brief Specialization of Locator_t used to hold UDP IPv4 locators using a
 * more compact representation. Equivalent to Locator_t with kind set to
 * LOCATOR_KIND_UDPv4.
 * Need only be able to hold an IPv4 address and a port number.
 *
 * The mapping between the dot-notation “a.b.c.d” of an IPv4 address and its
 * representation as an unsigned long is as follows:
 * address = (((a*256 + b)*256) + c)*256 + d
 */
typedef struct LocatorUDPv4_t {
  unsigned long address;
  unsigned long port;
} LocatorUDPv4_t;

/**
 * @brief
 */
 #define SIZE_SEQUENCE_NUM_SET_BITMAP 8
typedef struct SequenceNumberSet_t {
  SequenceNumber_t bitmapBase;
  uint32_t numBits;
  int32_t bitmap[8];
} SequenceNumberSet_t;

#define LOCATORUDPv4_INVALID {0, 0}

/** @} */ // doxygen group RTPS_TYPES
#ifdef __cplusplus
}
#endif
#endif //TINY_RTPS_RTPS_TYPES_H
