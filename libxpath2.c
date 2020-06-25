#include "libxpath2.h"
#include <ctype.h>
#include <libxml/xpathInternals.h>
#include <libxml/xmlregexp.h>

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
	xmlXPathRegisterFunc(ctx, BAD_CAST "matches", xpath2MatchesFunction);
	xmlXPathRegisterFunc(ctx, BAD_CAST "lower-case", xpath2LowerCaseFunction);
	xmlXPathRegisterFunc(ctx, BAD_CAST "upper-case", xpath2UpperCaseFunction);
}
