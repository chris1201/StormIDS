/*
 * Use at your own risk.
 *
 * Copyright (C) 2005-2008 Sourcefire, Inc.
 * 
 * This file is autogenerated via rules2c, by Brian Caswell <bmc@sourcefire.com>
 */

/*

alert tcp $EXTERNAL_NET $HTTP_PORTS -> $HOME_NET any (msg:"WEB-CLIENT Microsoft
Excel malformed ftCMO record remote code execution attempt"; flow:
to_client,established; flowbits:isset,file.xls; content:"|15 00 12 00 08
00|"; fast_pattern; content:"|5D 00|"; distance: -10; within: 2; content:"|09
08 10 00 00 06 10 00|"; classtype: attempted-user; reference: cve, 2009-0100;
reference:url,technet.microsoft.com/en-us/security/bulletin/MS09-009;
metadata: policy balanced-ips drop, policy security-ips drop, service http;
sid: 15465;)

An attack consists of the following object record:
|5d 00| . . |15 00 12 00 08 00|

occuring prior to a valid MSO Picture Group, which begins with record type:
|EC 00|

We're insisting that we see the begining of the worksheet:
|09 08 10 00 00 06 10 00|

to ensure that we aren't losing the EC 00 record due to packet segementation.
The EC 00 record is large enough that this could reasonably occur.

*/


#include "sf_snort_plugin_api.h"
#include "sf_snort_packet.h"


/* declare detection functions */
int rule15465eval(void *p);

/* declare rule data structures */
/* precompile the stuff that needs pre-compiled */
/* flow:established, to_client; */
static FlowFlags rule15465flow0 = 
{
    FLOW_ESTABLISHED|FLOW_TO_CLIENT
};

static RuleOption rule15465option0 =
{
    OPTION_TYPE_FLOWFLAGS,
    {
        &rule15465flow0
    }
};
/* flowbits:isset "file.xls"; */
static FlowBitsInfo rule15465flowbits1 =
{
    "file.xls",
    FLOWBIT_ISSET,
    0,
};

static RuleOption rule15465option1 =
{
    OPTION_TYPE_FLOWBIT,
    {
        &rule15465flowbits1
    }
};
#ifndef CONTENT_FAST_PATTERN
#define CONTENT_FAST_PATTERN 0
#endif
// content:"|15 00 12 00 08 00|", depth 0, fast_pattern; 
static ContentInfo rule15465content2 = 
{
    (uint8_t *) "|15 00 12 00 08 00|", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_FAST_PATTERN|CONTENT_BUF_NORMALIZED|CONTENT_RELATIVE, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15465option2 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15465content2
    }
};
// content:"]|00|", offset -10, depth 2, relative; 
static ContentInfo rule15465content3 = 
{
    (uint8_t *) "]|00|", /* pattern (now in snort content format) */
    2, /* depth */
    -10, /* offset */
    CONTENT_RELATIVE|CONTENT_BUF_NORMALIZED, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15465option3 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15465content3
    }
};
// content:"|09 08 10 00 00 06 10 00|", depth 0; 
static ContentInfo rule15465content4 = 
{
    (uint8_t *) "|09 08 10 00 00 06 10 00|", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_BUF_NORMALIZED|CONTENT_RELATIVE, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15465option4 = 
{
    OPTION_TYPE_CONTENT,
    {
        &rule15465content4
    }
};

static ContentInfo rule15465content5 =
{
    (uint8_t *) "|EC 00|", /* pattern (now in snort content format) */
    0, /* depth */
    0, /* offset */
    CONTENT_BUF_NORMALIZED|CONTENT_RELATIVE, /* flags */
    NULL, /* holder for boyer/moore PTR */
    NULL, /* more holder info - byteform */
    0, /* byteform length */
    0 /* increment length*/
};

static RuleOption rule15465option5 =
{
    OPTION_TYPE_CONTENT,
    {
        &rule15465content5
    }
};


/* references for sid 15465 */
/* reference: cve "2009-0100"; */
static RuleReference rule15465ref1 = 
{
    "cve", /* type */
    "2009-0100" /* value */
};

/* reference: url "technet.microsoft.com/en-us/security/bulletin/MS09-009"; */
static RuleReference rule15465ref2 = 
{
    "url", /* type */
    "technet.microsoft.com/en-us/security/bulletin/MS09-009" /* value */
};

static RuleReference *rule15465refs[] =
{
    &rule15465ref1,
    &rule15465ref2,
    NULL
};
/* metadata for sid 15465 */
/* metadata:service http, policy balanced-ips drop, policy security-ips drop; */
static RuleMetaData rule15465service1 = 
{
    "service http"
};


//static RuleMetaData rule15465policy1 = 
//{
//    "policy balanced-ips drop"
//};
//
//static RuleMetaData rule15465policy2 = 
//{
//    "policy security-ips drop"
//};


static RuleMetaData *rule15465metadata[] =
{
    &rule15465service1,
//    &rule15465policy1,
//    &rule15465policy2,
    NULL
};

RuleOption *rule15465options[] =
{
    &rule15465option0,
    &rule15465option1,
    &rule15465option2,
    &rule15465option3,
    &rule15465option4,
    &rule15465option5,
    NULL
};

Rule rule15465 = {
   
   /* rule header, akin to => tcp any any -> any any               */{
       IPPROTO_TCP, /* proto */
       "$EXTERNAL_NET", /* SRCIP     */
       "$HTTP_PORTS", /* SRCPORT   */
   
       0, /* DIRECTION */
       "$HOME_NET", /* DSTIP     */
   
       "any", /* DSTPORT   */
   },
   /* metadata */
   { 
       3,  /* genid */
       15465, /* sigid */
       7, /* revision */
   
       "attempted-user", /* classification */
       0,  /* hardcoded priority XXX NOT PROVIDED BY GRAMMAR YET! */
       "FILE-OFFICE Microsoft Excel malformed object record remote code execution attempt",     /* message */
       rule15465refs /* ptr to references */
       ,rule15465metadata
   },
   rule15465options, /* ptr to rule options */
   &rule15465eval, /* use the built in detection function */
   0 /* am I initialized yet? */
};


/* detection functions */
int rule15465eval(void *p) {
   const uint8_t *cursor_normal, *end_of_payload;
   const uint8_t *cursor_obj;
   const uint8_t *cursor_mpg;
   SFSnortPacket *sp = (SFSnortPacket *) p;

   if(sp == NULL)
      return RULE_NOMATCH;

   if(sp->payload == NULL)
      return RULE_NOMATCH;
    
   // flow:established, to_client;
   if(checkFlow(p, rule15465options[0]->option_u.flowFlags) <= 0 )
      return RULE_NOMATCH;

   // flowbits:isset "file.xls";
   if(processFlowbits(p, rule15465options[1]->option_u.flowBit) <= 0)
      return RULE_NOMATCH;

   if(getBuffer(sp, CONTENT_BUF_NORMALIZED, &cursor_normal, &end_of_payload) <= 0)
      return RULE_NOMATCH;

   // content:"|09 08 10 00 00 06 10 00|", depth 0;
   while(contentMatch(p, rule15465options[4]->option_u.content, &cursor_normal) > 0) {
      cursor_obj = cursor_normal;
      cursor_mpg = cursor_normal;

      //content:"|15 00 12 00 08 00|", depth 0, fast_pattern;
      if(contentMatch(p, rule15465options[2]->option_u.content, &cursor_obj) <= 0)
         return RULE_NOMATCH;

      // content:"]|00|", offset -10, depth 2, relative;
      if(contentMatch(p, rule15465options[3]->option_u.content, &cursor_obj) > 0) {

         // content:"|ec 00|";
         if(contentMatch(p, rule15465options[5]->option_u.content, &cursor_mpg) <= 0)
            return RULE_MATCH;

         if(cursor_obj < cursor_mpg)
            return RULE_MATCH;
      }
   }
   return RULE_NOMATCH;
}

/*
Rule *rules[] = {
    &rule15465,
    NULL
};
*/

