/* tests */
open TestTypes;

let runTest = (test: test): testResult => {
    switch (test) {
    | Test(title, func) => (func() === true) ? TestPass(title) : TestFail(title)
    | _ => TestSkip("Invalid or skipped test")
    };
};

let doTests = (tests: list(test)): list(testResult) => {
    List.map(runTest, tests);
};

let printTestResult = (testResult: testResult) => {
    let string = switch (testResult) {
    | TestPass(title) => "+++ PASS: " ++ title ++ "\n"
    | TestFail(title) => "--- FAIL: " ++ title ++ "\n"
    };
    print_string(string);
};

let printTestResults = (testResults) => {
    List.iter(printTestResult, testResults);
};