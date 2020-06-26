#include "libxpath2.h"
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <libxml/tree.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlregexp.h>
#include <libxml/xmlstring.h>

static void xpath2AbsFunction(xmlXPathParserContextPtr ctx, int nargs)
{
	double arg1;

	if (nargs != 1) {
		xmlXPathSetArityError(ctx);
		return;
	}

	arg1 = xmlXPathPopNumber(ctx);

	xmlXPathReturnNumber(ctx, fabs(arg1));
}

static void xpath2CompareFunction(xmlXPathParserContextPtr ctx, int nargs)
{
	xmlChar *arg1, *arg2;
	int c;

	if (nargs != 2) {
		xmlXPathSetArityError(ctx);
		return;
	}

	arg2 = xmlXPathPopString(ctx);
	arg1 = xmlXPathPopString(ctx);

	c = xmlStrcmp(arg1, arg2);

	xmlFree(arg1);
	xmlFree(arg2);

	if (c < 0) {
		xmlXPathReturnNumber(ctx, -1);
	} else if (c > 0) {
		xmlXPathReturnNumber(ctx, 1);
	} else{
		xmlXPathReturnNumber(ctx, 0);
	}
}

static void xpath2EndsWithFunction(xmlXPathParserContextPtr ctx, int nargs)
{
	xmlChar *arg1, *arg2;
	int len1, len2;

	if (nargs != 2) {
		xmlXPathSetArityError(ctx);
		return;
	}

	arg2 = xmlXPathPopString(ctx);
	arg1 = xmlXPathPopString(ctx);

	len1 = xmlStrlen(arg1);
	len2 = xmlStrlen(arg2);

	if (len1 < len2) {
		xmlXPathReturnBoolean(ctx, false);
	} else {
		xmlXPathReturnBoolean(ctx, xmlStrcmp(arg1 + (len1 - len2), arg2) == 0);
	}
}

static void xpath2LowerCaseFunction(xmlXPathParserContextPtr ctx, int nargs)
{
	xmlChar *arg1;
	int i;

	if (nargs != 1) {
		xmlXPathSetArityError(ctx);
		return;
	}

	arg1 = xmlXPathPopString(ctx);

	for (i = 0; arg1[i]; ++i) {
		arg1[i] = tolower(arg1[i]);
	}

	xmlXPathReturnString(ctx, arg1);
}

static void xpath2MatchesFunction(xmlXPathParserContextPtr ctx, int nargs)
{
	xmlChar *arg1, *arg2;
	xmlRegexpPtr regex;

	if (nargs != 2) {
		xmlXPathSetArityError(ctx);
		return;
	}

	arg2 = xmlXPathPopString(ctx);
	arg1 = xmlXPathPopString(ctx);
	regex = xmlRegexpCompile(arg2);

	xmlXPathReturnBoolean(ctx, xmlRegexpExec(regex, arg1));

	xmlRegFreeRegexp(regex);
	xmlFree(arg1);
	xmlFree(arg2);
}

static void xpath2TokenizeFunction(xmlXPathParserContextPtr ctx, int nargs)
{
	xmlChar *arg1, *arg2;
	char *token = NULL, *end = NULL;
	xmlXPathObjectPtr obj;

	if (nargs < 1 || nargs > 2) {
		xmlXPathSetArityError(ctx);
		return;
	}

	if (nargs > 1) {
		arg2 = xmlXPathPopString(ctx);
	} else {
		arg2 = xmlCharStrdup(" ");
	}
	arg1 = xmlXPathPopString(ctx);

	obj = xmlXPathNewNodeSet(NULL);

	/* FIXME: strtok_r is a poor way to handle this. arg2 is a regexp, not
	 *        necessarily a literal separator. */
	while ((token = strtok_r(token ? NULL : (char *) arg1, (char *) arg2, &end))) {
		xmlXPathNodeSetAdd(obj->nodesetval, xmlNewText(BAD_CAST token));
	}

	xmlXPathReturnNodeSet(ctx, obj->nodesetval);

	xmlFree(arg1);
	xmlFree(arg2);
}

static void xpath2UpperCaseFunction(xmlXPathParserContextPtr ctx, int nargs)
{
	xmlChar *arg1;
	int i;

	if (nargs != 1) {
		xmlXPathSetArityError(ctx);
		return;
	}

	arg1 = xmlXPathPopString(ctx);

	for (i = 0; arg1[i]; ++i) {
		arg1[i] = toupper(arg1[i]);
	}

	xmlXPathReturnString(ctx, arg1);
}

void xpath2RegisterFunctions(xmlXPathContextPtr ctx)
{
	xmlXPathRegisterFunc(ctx, BAD_CAST "abs", xpath2AbsFunction);
	xmlXPathRegisterFunc(ctx, BAD_CAST "compare", xpath2CompareFunction);
	xmlXPathRegisterFunc(ctx, BAD_CAST "ends-with", xpath2EndsWithFunction);
	xmlXPathRegisterFunc(ctx, BAD_CAST "lower-case", xpath2LowerCaseFunction);
	xmlXPathRegisterFunc(ctx, BAD_CAST "matches", xpath2MatchesFunction);
	xmlXPathRegisterFunc(ctx, BAD_CAST "upper-case", xpath2UpperCaseFunction);
	xmlXPathRegisterFunc(ctx, BAD_CAST "tokenize", xpath2TokenizeFunction);
}
