#version 130

// Input vertex data, different for all executions of this shader.
in vec2 vertexPosition_screenspace;
in vec2 vertexUV;

// Output data ; will be interpolated for each fragment.
out vec2 UV;

void main(){

	// Output position of the vertex, in clip space
	// map [0..800][0..600] to [-1..1][-1..1]
	vec2 vertexPosition_homoneneousspace = vertexPosition_screenspace - vec2(400,400); // [0..800][0..600] -> [-400..400][-300..300]
	vertexPosition_homoneneousspace /= vec2(400,400);
	gl_Position =  vec4(vertexPosition_homoneneousspace,0,1);
	
	// UV of the vertex. No special space for this one.
	UV = vertexUV;
}
