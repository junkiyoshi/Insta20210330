#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetLineWidth(2);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.begin();

	for (int x = ofGetWidth() * -0.5; x <= ofGetWidth() * 0.5; x += 30) {

		ofMesh face, line;
		line.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);

		for (int y = 0; y <= ofGetHeight(); y += 1) {

			auto noise_value = ofNoise(x * 0.005, y * 0.001 + ofGetFrameNum() * 0.005);
			float angle = 0;
			if (noise_value > 0.75) { angle = ofMap(noise_value, 0.75, 1.0, 0, PI * 0.2); }
			if (noise_value < 0.25) { angle = ofMap(noise_value, 0.25, 0.0, 0, PI * -0.2); }
			auto rotation = glm::rotate(glm::mat4(), angle, glm::vec3(1, 0, 0));

			face.addVertex(glm::vec4(x - 13, y, 0, 0) * rotation);
			face.addVertex(glm::vec4(x + 13, y, 0, 0) * rotation);

			line.addVertex(glm::vec4(x - 13, y, 0, 0) * rotation);
			line.addVertex(glm::vec4(x + 13, y, 0, 0) * rotation);

			if (face.getNumVertices() > 2) {

				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 2); face.addIndex(face.getNumVertices() - 4);
				face.addIndex(face.getNumVertices() - 1); face.addIndex(face.getNumVertices() - 3); face.addIndex(face.getNumVertices() - 4);

				line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 3);
				line.addIndex(line.getNumVertices() - 2); line.addIndex(line.getNumVertices() - 4);
			}
		}

		line.addIndex(0); line.addIndex(1);
		line.addIndex(line.getNumVertices() - 1); line.addIndex(line.getNumVertices() - 2);

		ofSetColor(239);
		face.draw();
		ofSetColor(39);
		line.drawWireframe();
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}