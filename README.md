
<h1 align="center">
	🪄 pipex
</h1>

## 💡 О проекте:

> _Этот проект направлен на углубление вашего понимания двух уже известных вам концепций: Redirections и Pipes. Это вводный проект для более крупных проектов UNIX, которые появятся позже в этом курсе.._
	
	Этот проект состоит в воспроизведении поведения shell pipe, перенаправляя STDIN
	и STDOUT с помощью pipe().
	Pipex - это индивидуальный проект в 42, который требует от нас создания программы,
	имитирующей поведение shell pipe, принимающей файл или читающей из STDIN и
	перенаправляющей на последовательность команд, которые будут записаны в выходной файл.
	Для создания программы необходимо создать дочерние процессы с помощью fork(),
	взаимодействующие с родительским процессом через pipe(), манипулирующие 
	переменной окружения, проверяющие, существует ли команда или имеет ли она
	разрешение на выполнение, например, печатающие ошибки в STDERR, когда это необходимо,
	возвращающие правильный код состояния.

Более подробно о проекте можно посмотреть в  [**subject**](https://github.com/AYglazk0v/pipex/blob/master/en.subject.pdf).

## 🛠 Тестирование и использование:

	# Клонируйте проект и получите доступ к папке
	git clone git@github.com:AYglazk0v/pipex.git && cd pipex/
	# Запустите make, чтобы вы могли собрать программу с обязательной частью
	make
	# Создайте файл для использования в программе input
	echo "aaaaaaaaaaaaaaaaaaaaaaaaaa" > input_file
	# Запустите программу, как показано в примере
	./pipex "input_file" "tr a b" "tr b c" "output_file"
	# Проверьте выходной файл
	cat output_file
	# или
	# Запустите make bonus, чтобы собрать программу с бонусной частью
	make bonus
	# Запустите программу, как показано в примере
	./pipex "here_doc" "END" "tr a b" "tr b c" "tr c d" "output_file"
	# Проверьте выходной файл
	cat output_file
	# Очистите выходные файлы с помощью
	make fclean

Для проверки работы можно сравнить поведение написанной программы и любого командного интерпретатора, в данном примере -- shell:
	

	 1. pipex ./pipex "input_file" "tr a b" "tr b c" "output_file"
		shell < input_file tr a b | tr b c > output_file
	 2.	pipex ./pipex "input_file" "ls -l" "wc -l" "output_file"
		shell < input_file ls -l | wc -l > output_file
	 3.	pipex ./pipex "here_doc" "END" "rev" "sort -r" "tr '\n' ' ' '" "output_file"
		shell << END rev | sort -r | tr '\n' ' ' ' >> output_file
