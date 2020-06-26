#include <libxml/xpath.h>
#include "libxpath2.h"

int test(const char *expr, xmlXPathContextPtr ctx)
{
	xmlXPathObjectPtr obj;
	int ret;

	obj = xmlXPathEval(BAD_CAST expr, ctx);

	ret = obj && obj->boolval;

	printf("[%s] %s\n",
		ret ? "PASS" : "FAIL",
		expr);

	xmlXPathFreeObject(obj);

	return ret;
}

int main(int argc, char **argv)
{
	xmlXPathContextPtr ctx;
	int total = 0, passed = 0;

	ctx = xmlXPathNewContext(NULL);
	xpath2RegisterFunctions(ctx);

	++total; passed += test("abs(-5) = 5", ctx);
	++total; passed += test("compare('abc', 'def') = -1", ctx);
	++total; passed += test("ends-with('abcdef', 'def')", ctx);
	++total; passed += test("lower-case('ABC') = 'abc'", ctx);
	++total; passed += test("matches('a', 'a')", ctx);
	++total; passed += test("upper-case('abc') = 'ABC'", ctx);
	++total; passed += test("tokenize('a b c')[1] = 'a'", ctx);
	++total; passed += test("tokenize('a,b,c', ',')[2] = 'b'", ctx);
	++total; passed += test("tokenize('a\tb\tc', '\t')[3] = 'c'", ctx);

	xmlXPathFreeContext(ctx);

	printf("%d of %d tests passed.\n", passed, total);

	return 0;
}
