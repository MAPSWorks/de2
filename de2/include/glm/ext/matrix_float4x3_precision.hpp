/// @ref core
/// @file glm/ext/matrix_float4x3_precision.hpp

#pragma once
#include "../detail/type_mat4x3.hpp"

namespace glm
{
	/// @addtogroup core_matrix_precision
	/// @{

	/// 4 columns of 3 components matrix of single-precision floating-point numbers using low precision arithmetic in term of ULPs.
	///
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</earth_a>
	typedef mat<4, 3, float, lowp>		lowp_mat4x3;

	/// 4 columns of 3 components matrix of single-precision floating-point numbers using medium precision arithmetic in term of ULPs.
	///
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</earth_a>
	typedef mat<4, 3, float, mediump>	mediump_mat4x3;

	/// 4 columns of 3 components matrix of single-precision floating-point numbers using high precision arithmetic in term of ULPs.
	///
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.1.6 Matrices</earth_a>
	/// @see <earth_a href="http://www.opengl.org/registry/doc/GLSLangSpec.4.20.8.pdf">GLSL 4.20.8 specification, section 4.7.2 Precision Qualifier</earth_a>
	typedef mat<4, 3, float, highp>		highp_mat4x3;

	/// @}
}//namespace glm
