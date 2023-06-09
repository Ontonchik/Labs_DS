#include <iostream>
#include <windows.h>

wchar_t const* mes[4]{
	L"W_Exit",L"W_A",L"W_B",L"W_C"
};

int main() {
	HANDLE hMutex = OpenMutex(SYNCHRONIZE, FALSE, L"Mutex");
	WaitForSingleObject(hMutex, INFINITE);
	std::cout << "hi";
	HANDLE mesEv[4];
	for (int i = 0; i < 4; ++i)
		mesEv[i] = OpenEvent(EVENT_MODIFY_STATE, FALSE, mes[i]);
	while (true) {
		std::string line;
		std::cin >> line;
		line = "W_" + line;
		std::wstring wline(line.begin(), line.end());
		if (wline._Equal(mes[0])) {
			SetEvent(mesEv[0]);
			break;
		}
		for (int i = 1; i < 4; ++i)
			if (wline._Equal(mes[i])) {
				SetEvent(mesEv[i]);
				break;
			}
	}
	ReleaseMutex(hMutex);
}
