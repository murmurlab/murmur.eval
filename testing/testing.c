#include "testing.h"

void    init_test(t_test *test, t_try *trys[])
{
    size_t x;
    size_t y;

    for (x = 0; trys[x]; x++)
        ;
	test->tests = malloc(x * sizeof(void *));
    for (x = 0; trys[x]; x++)
    {
        for (y = 0; (size_t)trys[x][y + 1].try; y++)
            ;
        test->tests[x] = malloc(y * sizeof(t_tests));
    }

    for (size_t j = 0; (size_t)trys[j]; j++)
    {
        for (size_t i = 0; (size_t)trys[j][i + 1].try; i++)
        {
            test->tests[j][i].test_fun = ((t_fun *)trys[j][0].try)->test_fun;
            test->tests[j][i].ko_msg = ((t_fun *)trys[j][0].try)->ko_msg;
            test->tests[j][i].ok_msg = ((t_fun *)trys[j][0].try)->ok_msg;
            test->tests[j][i].name = trys[j][0].expected;
            test->tests[j][i].trys = trys[j] + i + 1;
        }
    }

	test->fails = NULL;
	test->success = NULL;
}

void	tester(int test_group_num, int test_number, t_test *test)
{
	int		result;

	test->test_number = test_number;
	test->test_group_num = test_group_num;
    test->current_test = test->tests[test_group_num] + test_number;
	result = test->current_test->test_fun(test);
	if (result)
        test->current_test->ok_msg(test);
	else
	{
		ft_lstadd_back(&test->fails, ft_lstnew((void *)(size_t)(test_number)));
		test->current_test->ko_msg(test);
	}
}

