#pragma once

class System {
public:
	static void initialize();
	static void shutdown();
	static System* get_instance();

private:
	System();
	~System();

	static void at_exit();

	static System* instance;
};
