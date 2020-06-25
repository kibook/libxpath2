#include <libxml/xpath.h>
#include "libxpath2.h"

void test(const char *expr, xmlXPathContextPtr ctx)
{
	xmlXPathObjectPtr obj;

	obj = xmlXPathEval(BAD_CAST expr, ctx);

	printf("[%s] %s\n",
		obj && obj->boolval ? "PASS" : "FAIL",
		expr);

	xmlXPathFreeObject(obj);
}

int main(int argc, char **argv)
{
	xmlXPathContextPtr ctx;

	ctx = xmlXPathNewContext(NULL);
	xpath2RegisterFunctions(ctx);

	test("abs(-5) = 5", ctx);
	test("compare('abc', 'def') = -1", ctx);
	test("ends-with('abcdef', 'def')", ctx);
	test("lower-case('ABC') = 'abc'", ctx);
	test("matches('a', 'a')", ctx);
	test("upper-case('abc') = 'ABC'", ctx);

	xmlXPathFreeContext(ctx);

	return 0;
}
