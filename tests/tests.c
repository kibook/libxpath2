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

	puts("== abs ==");
	++total; passed += test("abs(10.5) = 10.5", ctx);
	++total; passed += test("abs(-10.5) = 10.5", ctx);
	puts("");

	puts("== compare ==");
	++total; passed += test("compare('abc', 'abc') = 0", ctx);
	++total; passed += test("compare('abc', 'def') = -1", ctx);
	++total; passed += test("compare('def', 'abc') = 1", ctx);
	puts("");

	puts("== ends-with ==");
	++total; passed += test("ends-with('tattoo', 'tattoo') = true()", ctx);
	++total; passed += test("ends-with('tattoo', 'atto') = false()", ctx);
	++total; passed += test("ends-with('', '') = true()", ctx);
	puts("");

	puts("== lower-case ==");
	++total; passed += test("lower-case('ABc!D') = 'abc!d'", ctx);
	puts("");

	puts("== matches ==");
	++total; passed += test("matches('abracadabra', 'bra') = true()", ctx);
	++total; passed += test("matches('abracadabra', '^a.*a$') = true()", ctx);
	++total; passed += test("matches('abracadabra', '^bra') = false()", ctx);
	puts("");

	puts("== upper-case ==");
	++total; passed += test("upper-case('abc') = 'ABC'", ctx);
	puts("");

	puts("== tokenize ==");
	++total; passed += test("tokenize(' red green blue ')[1] = 'red'", ctx);
	++total; passed += test("tokenize(' red green blue ')[2] = 'green'", ctx);
	++total; passed += test("tokenize(' red green blue ')[3] = 'blue'", ctx);
	++total; passed += test("tokenize('The cat sat on the mat', '\\s+')[1] = 'The'", ctx);
	++total; passed += test("tokenize('The cat sat on the mat', '\\s+')[2] = 'cat'", ctx);
	++total; passed += test("tokenize('The cat sat on the mat', '\\s+')[3] = 'sat'", ctx);
	++total; passed += test("tokenize('The cat sat on the mat', '\\s+')[4] = 'on'", ctx);
	++total; passed += test("tokenize('The cat sat on the mat', '\\s+')[5] = 'the'", ctx);
	++total; passed += test("tokenize('The cat sat on the mat', '\\s+')[6] = 'mat'", ctx);
	++total; passed += test("tokenize(' red green blue ', '\\s+')[1] = ''", ctx);
	++total; passed += test("tokenize(' red green blue ', '\\s+')[2] = 'red'", ctx);
	++total; passed += test("tokenize(' red green blue ', '\\s+')[3] = 'green'", ctx);
	++total; passed += test("tokenize(' red green blue ', '\\s+')[4] = 'blue'", ctx);
	++total; passed += test("tokenize(' red green blue ', '\\s+')[5] = ''", ctx);
	++total; passed += test("tokenize('1, 15, 24, 50', ',\\s*')[1] = '1'", ctx);
	++total; passed += test("tokenize('1, 15, 24, 50', ',\\s*')[2] = '15'", ctx);
	++total; passed += test("tokenize('1, 15, 24, 50', ',\\s*')[3] = '24'", ctx);
	++total; passed += test("tokenize('1, 15, 24, 50', ',\\s*')[4] = '50'", ctx);
	++total; passed += test("tokenize('1,15,,24,50,', ',')[1] = '1'", ctx);
	++total; passed += test("tokenize('1,15,,24,50,', ',')[2] = '15'", ctx);
	++total; passed += test("tokenize('1,15,,24,50,', ',')[3] = ''", ctx);
	++total; passed += test("tokenize('1,15,,24,50,', ',')[4] = '24'", ctx);
	++total; passed += test("tokenize('1,15,,24,50,', ',')[5] = '50'", ctx);
	++total; passed += test("tokenize('1,15,,24,50,', ',')[6] = ''", ctx);
	++total; passed += test("tokenize('Some unparsed <br> HTML <BR> text', '\\s*<br>\\s*', 'i')[1] = 'Some unparsed'", ctx);
	++total; passed += test("tokenize('Some unparsed <br> HTML <BR> text', '\\s*<br>\\s*', 'i')[2] = 'HTML'", ctx);
	++total; passed += test("tokenize('Some unparsed <br> HTML <BR> text', '\\s*<br>\\s*', 'i')[3] = 'text'", ctx);
	puts("");

	xmlXPathFreeContext(ctx);

	printf("%d of %d tests passed.\n", passed, total);

	return 0;
}
