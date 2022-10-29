#include "ClickRecorder.h"
using namespace DrillClickRecorder;

int main() {
	ClickRecorder^ mainWin = gcnew ClickRecorder;
	Application::Run(mainWin);
}