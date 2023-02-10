# include <string_view>
#include "../glm/glm/glm.hpp"
#include "../glm/glm/gtc/matrix_transform.hpp"
#include "../glm/glm/gtc//random.hpp"

class IRenderer {
	public:
		IRenderer(): m_mView(1.0f), m_mProjection(1.0f), m_vLightPosition(0.0f, 1.0f, 0.0f) {

		}

		virtual bool Create() = 0;
		virtual void Flip() = 0;
		virtual void Clear(float r, float g, float b, float a, float depth = 1.0f, int32_t stencil = 0) = 0;

		void Clear(const glm::vec4& color, float depth = 1.0, int32_t stencil = 0) {
			Clear(color.r, color.g, color.b, color.a, depth, stencil);
		}

		virtual void SetViewport(const glm::ivec4& area) = 0;
		virtual bool SetTexture(
			uint32_t program,
			uint32_t texture,
			int32_t slot,
			const std::string_view& uniformName
		) = 0;

		glm::mat4& GetViewMatrix() { return m_mView; }
		const glm::mat4& GetViewMatrix() const { return m_mView; }

		glm::mat4& GetProjectionMatrix() { return m_mProjection; }
		const glm::mat4& GetProjectionMatrix() const { return m_mProjection; }

		void SetViewMatrix(const glm::mat4& m) { m_mView = m; }
		void SetProjectionMatrix(const glm::mat4& m) { m_mProjection = m; }

		const glm::vec3& GetLightPosition() const { return m_vLightPosition; }
		void SetLightPosition(const glm::vec3& pos) { m_vLightPosition = pos; }


	protected:
		glm::mat4				m_mView;
		glm::mat4				m_mProjection;
		glm::vec3				m_vLightPosition;

	private:

};