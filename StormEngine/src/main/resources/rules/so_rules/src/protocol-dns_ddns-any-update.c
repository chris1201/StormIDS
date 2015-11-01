/*
 * !!! XXX DOES NOT USE BUILT-IN DETECTION FUNCTION XXX !!!
 * 
 * alert udp $EXTERNAL_NET any -> $HOME_NET 53 (msg:"BAD-TRAFFIC BIND named 9 dynamic update message remote dos attempt"; flow:to_server,established;  content:"|28 00 00 01 00 01|"; offset:2; depth:6; metadata:policy security-ips drop, policy balanced-ips drop; reference:cve,2009-0696; reference:url, www.isc.org/software/bind/advisories/cve-2009-0696; classtype:attempted-dos; sid:15734; rev:1;)
 *
*/
/*
 * Use at your own risk.
 *
 * Copyright (C) 2005-2008 Sourcefire, Inc.
 * 
 * This file is autogenerated via rules2c, by Brian Caswell <bmc@sourcefire.com>
 */


#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"

#include <string.h>

#include "so-util_dns.h"

//#define DEBUG
#ifdef DEBUG
#define DEBUG_WRAP(code) code
#else
#define DEBUG_WRAP(code)
#endif


/* declare detection functions */
int rule15734eval(void *p);

/* declare rule data structures */
/* precompile the stuff that needs pre-compiled */
/* flow:established, to_server; */
static FlowFlags rule15734flow0 = 
{
    FLOW_ESTABLISHED|FLOW_TO_SERVER
};

static RuleOption rule15734option0 =
{
    OPTION_TYPE_FLOWFLAGS,
    {
        &rule15734flow0
    }
};
#ifndef CONTENT_FAST_PATTERN
#define CONTENT_FAST_PATTERN 0
#endif
// content:"|28 00 00 01 00 01|", offset 2, depth 6, fast_pattern; 
static ContentInfo rule15734content1 = 
{
    (uint8_t *) "|28 00 00 01 00 01|", /* pattern (now in snort content format) */
    6, /* depth */
    2, /* offset */
    CONTENT_FAST_PATTERN|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15734option1 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15734content1
    }
};

/* references for sid 15734 */
/* reference: cve "2009-0696"; */
static RuleReference rule15734ref1 = 
{
    "cve", /* type */
    "2009-0696" /* value */
};

/* reference: url "www.isc.org/software/bind/advisories/cve-2009-0696"; */
static RuleReference rule15734ref2 = 
{
    "url", /* type */
    "www.isc.org/software/bind/advisories/cve-2009-0696" /* value */
};

static RuleReference *rule15734refs[] =
{
    &rule15734ref1,
    &rule15734ref2,
    NULL
};

/* metadata for sid 15734 */
/* metadata:policy balanced-ips drop, policy security-ips drop; */

//static RuleMetaData rule15734policy1 = 
//{
//    "policy balanced-ips drop"
//};
//
//static RuleMetaData rule15734policy2 = 
//{
//    "policy security-ips drop"
//};

static RuleMetaData rule15734policy3 =
{
    "service dns"
};


static RuleMetaData *rule15734metadata[] =
{
//    &rule15734policy1,
//    &rule15734policy2,
    &rule15734policy3,
    NULL
};

RuleOption *rule15734options[] =
{
    &rule15734option0,
    &rule15734option1,
    NULL
};

Rule rule15734 = {
   
   /* rule header, akin to => tcp any any -> any any               */{
       IPPROTO_UDP, /* proto */
       "$EXTERNAL_NET", /* SRCIP     */
       "any", /* SRCPORT   */
   
       0, /* DIRECTION */
       "$HOME_NET", /* DSTIP     */
       "53", /* DSTPORT   */
   },
   /* metadata */
   { 
       3,  /* genid */
       15734, /* sigid */
       5, /* revision */
       "attempted-dos", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "PROTOCOL-DNS BIND named 9 dynamic update message remote dos attempt",     /* message */
       rule15734refs /* ptr to references */
       ,rule15734metadata
   },
   rule15734options, /* ptr to rule options */
   &rule15734eval, /* use the built in detection function */
   0 /* am I initialized yet? */
};


/* detection functions */
int rule15734eval(void *p) {
   const uint8_t *cursor_raw = 0, *end_of_payload;
   SFSnortPacket *sp = (SFSnortPacket *) p;

   const uint8_t *junkptr; // for getBuffer()

   uint16_t num_updates;
   uint16_t num_addtl_rrs;
   uint16_t data_len;
   uint16_t record_type;

   // cruft
   int i;

   if(sp == NULL)
      return RULE_NOMATCH;

   if(sp->payload == NULL)
      return RULE_NOMATCH;
    
   // flow:established, to_server;
//   if(checkFlow(p, rule15734options[0]->option_u.flowFlags) <= 0 )
//      return RULE_NOMATCH;

   // content:"|28 00 00 01 00 01|", offset 2, depth 6, fast_pattern;
   if(contentMatch(p, rule15734options[1]->option_u.content, &cursor_raw) <= 0)
      return RULE_NOMATCH;

   DEBUG_WRAP(printf("passed content\n"));

   if(getBuffer(p, CONTENT_BUF_NORMALIZED, &junkptr, &end_of_payload) <= 0)
      return RULE_NOMATCH;

   if(cursor_raw + 25 >= end_of_payload)
      return RULE_NOMATCH;

   num_updates = *cursor_raw++ << 8;
   num_updates |= *cursor_raw++;

   DEBUG_WRAP(printf("num_updates=%d\n", num_updates));

   if(num_updates == 0)
      return RULE_NOMATCH;

   num_addtl_rrs = *cursor_raw++ << 8;
   num_addtl_rrs |= *cursor_raw++;

   DEBUG_WRAP(printf("num_addtl_rrs=%d\n", num_addtl_rrs));

   // Zone section (we force this to be one entry by content match)
   if(dns_skip_name(&cursor_raw, end_of_payload) <= 0)
      return RULE_NOMATCH;

   if(cursor_raw + 18 >= end_of_payload)
      return RULE_NOMATCH;

   DEBUG_WRAP(printf("SOA: 0x%02x%02x Class: 0x%02x%02x\n", cursor_raw[0], cursor_raw[1],cursor_raw[2],cursor_raw[3]));

   // Verify Type: SOA and Class: IN
   if(memcmp(cursor_raw, "\x00\x06\x00\x01", 4))
      return RULE_NOMATCH;

   cursor_raw += 4;

   // Prerequisites section (we force this to be one entry by content match)
   if(dns_skip_name(&cursor_raw, end_of_payload) <= 0)
      return RULE_NOMATCH;

   if(cursor_raw + 14 >= end_of_payload)
      return RULE_NOMATCH;

   // FP reduction.  Microsoft clients do ANY-ANY
   // Better solution is to make sure EXTERNAL_NET is set correctly
   // Verify Type: ANY Class: IN
   if(memcmp(cursor_raw, "\x00\xff\x00\x01", 4))
      return RULE_NOMATCH;

   cursor_raw += 8; // Skip over class and type and Skip TTL

   data_len = *cursor_raw++ << 8;
   data_len |= *cursor_raw++;     
   cursor_raw += data_len;   

   // Updates (YAY!!)
   DEBUG_WRAP(printf("Checking updates\n"));
   for(i = 0; i < num_updates; i++) {
      DEBUG_WRAP(printf("Checking update %d...", i));

      if(dns_skip_name(&cursor_raw, end_of_payload) <= 0)
         return RULE_NOMATCH;

      if(cursor_raw + 2 >= end_of_payload)
         return RULE_NOMATCH;
   
      record_type = *cursor_raw++ << 8;
      record_type |= *cursor_raw++;

      DEBUG_WRAP(printf("record_type 0x%04x\n", record_type));  
      // Alert if we see an update of type ANY (0x00FF) 
      if(record_type == 0x00FF)
         return RULE_MATCH;

      if(cursor_raw + 8 >= end_of_payload)
         return RULE_NOMATCH;

      cursor_raw += 6;

      data_len = *cursor_raw++ << 8;
      data_len |= *cursor_raw++;   
      cursor_raw += data_len;
   }

   // Currently, we don't care about the Additional RRs section, but if it turns
   // out we get false positives, we can add the requirement that there be no
   // TSIG (0x00fa) records aka unauthenticated update requests

   return RULE_NOMATCH;
}

/*
Rule *rules[] = {
    &rule15734,
    NULL
};
*/

