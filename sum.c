/*
 * Copyright 2019 Bruno Flores
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include <pthread.h>
#include <stdio.h>

int sum; /* this data is shared by the thread(s) */
void *runner(void *param); /* threads call this function */

int main(int argc, char *argv[])
{
	pthread_t tid; /* the thread identifier */
	pthread_attr_t attr; /* set of thread attributes */

	if (argc != 2) {
		fprintf(stderr, "usage: sum.out <integeger value>\n");
		return -1;
	}

	if (atoi(argv[1]) < 0) {
		fprintf(stderr, "%d must be >= 0\n", atoi(argv[1]));
		return -1;
	}

	/* get the default attributes */
	pthread_attr_init(&attr);
	/* create the thread */
	pthread_create(&tid, &attr, runner, argv[1]);
	/* wait for the thread to exit */
	pthread_join(tid, NULL);

	printf("sum = %d\n", sum);

	return 0;
}

void *runner(void *param)
{
	int i, upper = atoi(param);
	sum = 0;

	for (i = 1; i <= upper; i++)
		sum += i;

	pthread_exit(0);
}
