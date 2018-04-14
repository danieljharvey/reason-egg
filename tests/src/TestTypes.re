type testResult = TestPass(string) | TestFail (string) | TestSkip(string);
type nope = ();
type testFunction = nope => bool;

type test = Test(string, testFunction);