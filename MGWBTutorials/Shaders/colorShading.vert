#version 130
// The vertex shader operates on each vertex.

// Input data from the VBO. Each vertex is two floats.
in vec2 vertexPosition;
in vec4 vertexColor;
in vec2 vertexUV;

out vec2 fragmentPosition;
out vec4 fragmentColor;
out vec2 fragmentUV;

uniform mat4 projection;

void main() {
	// Set the x & y position on the screen.
	gl_Position.xy = (projection * vec4(vertexPosition, 0.0, 1.0)).xy;	
	// The z position is zero because we are in 2D.
	gl_Position.z = 0.0;
	
	// Indicate that the coordinates are normalized.
	gl_Position.w = 1.0;
	
	fragmentPosition = vertexPosition;
	fragmentColor = vertexColor;
	fragmentUV = vec2(vertexUV.x, 1.0 - vertexUV.y);	// unflip the y coordinate
}