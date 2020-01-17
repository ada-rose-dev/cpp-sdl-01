#include "goText.h"

using namespace go;

goText::goText() {

}
goText::~goText() {

}

void goText::Step() {
	preStep();

	postStep();
}

void goText::Render() {
	preRender();

	postRender();
}
