class Generator
{
public:
	int processID;
	double arrival_time;
	double service_time;
	double start_time;
	double finish_time;
	bool isDone = false;
	bool starting = true;
	Generator(){};
	Generator(int a, double b, double c)
	{
		processID = a+1;
		arrival_time = b;
		service_time = c;
	}
};

