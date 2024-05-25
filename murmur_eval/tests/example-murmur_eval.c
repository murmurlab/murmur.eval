#include "murmur_eval.h"
#include <string.h>
#include <stdio.h>

static int		ft_lstsize(struct s_link_list *lst);

int		ft_strlen_test(t_test *test);
void	ft_strlen_test_ko(t_test *test);
void	ft_strlen_test_ok(t_test *test);

void	*get_my_data(void)
{
	return (NULL);
}

void	test_main()
{
    NEW_TEST_RUNNER(1)
	GET_TEST_RUNNER(1).my_data = get_my_data();

	NEW_TEST(1)
        NEW_GROUP("ft_strlen test", ft_strlen_test, ft_strlen_test_ko, ft_strlen_test_ok)
		{
			CASE = "ahmet",
			EXPECTED = 5
		},
		{
			CASE = "1234567",
			EXPECTED = 7
		},
        END_GROUP
        NEW_GROUP("ft_strlen test2", ft_strlen_test, ft_strlen_test_ko, ft_strlen_test_ok)
		{
			CASE = "111",
			EXPECTED = 3333
		},
		{
			CASE = "3333",
			EXPECTED = 44
		},
        END_GROUP
    END_TEST

	EVAL_INIT(GET_TEST_RUNNER(1), GET_TEST(1))

	EVAL_ALL(GET_TEST_RUNNER(1), GET_TEST(1))

	// EVAL_GROUP(GET_TEST_RUNNER(1), GET_TEST(1), 0)

	// EVAL_TEST(GET_TEST_RUNNER(1), 0, 0)

	EVAL_FAILS(GET_TEST_RUNNER(1))

}
int		ft_strlen_test(t_test *test)
{
	CURR_TEST(test)->result = strlen(CURR_TEST(test)->try);
	if (CURR_TEST(test)->result == CURR_TEST(test)->expected)
		return (1);
	return (0);
}
void	ft_strlen_test_ko(t_test *test)
{
	printf("=============== %s ============\n", test->current_test->name);
	printf("try		[ %s ]\n", (char *)CURR_TEST(test)->try);
	printf(YELLOW"your		[ %zu ]\n"RESET, (size_t)(CURR_TEST(test)->result));
	printf("expected	[ %zu ]\n", (size_t)(CURR_TEST(test)->expected));
	printf("^^^^^^^^=========TEST %zu=%s================\n\n\n", test->test_number, __result_eval[1]);
}
void	ft_strlen_test_ok(t_test *test)
{
	printf("=============== %s ================\n", test->current_test->name);
    printf("try         	[ %s ]\n", (char *)CURR_TEST(test)->try);
    printf(GREEN"expected	[ %zu ]\n"RESET, (size_t)(CURR_TEST(test)->expected));
	printf("=================TEST %zu=%s================\n\n\n", test->test_number, __result_eval[0]);
}



static int	ft_lstsize(struct s_link_list *lst)
{
	size_t	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}