#pragma once

#include "Event.h"

namespace OpenGLRenderer {

	// app events may not be used, but here in case we need to; could be removed in the future
	class AppTickEvent : public Event {
	public:
		AppTickEvent() {}

		int GetCategoryFlags() const override {
			return EventCategoryApplication;
		}

		static EventType GetStaticType() { return EventType::AppTick; }

		EventType GetEventType() const override {
			return GetStaticType();
		}

		const char* GetName() const override {
			return "AppTick";
		}
	};

	class AppUpdateEvent : public Event {
		AppUpdateEvent() {}

		int GetCategoryFlags() const override {
			return EventCategoryApplication;
		}

		static EventType GetStaticType() { return EventType::AppUpdate; }

		EventType GetEventType() const override {
			return GetStaticType();
		}

		const char* GetName() const override {
			return "AppUpdate";
		}
	};

	class AppRenderEvent : public Event {
	public:
		AppRenderEvent() {}

		int GetCategoryFlags() const override {
			return EventCategoryApplication;
		}

		static EventType GetStaticType() { return EventType::AppRender; }

		EventType GetEventType() const override {
			return GetStaticType();
		}

		const char* GetName() const override {
			return "AppRender";
		}
	};

	// event triggers when the window is closed
	class WindowCloseEvent : public Event {
	public:
		WindowCloseEvent() {}

		static EventType GetStaticType() { return EventType::WindowClose; }

		EventType GetEventType() const {
			return GetStaticType();
		}

		const char* GetName() const {
			return "WindowClose";
		}

		int GetCategoryFlags() const override {
			return EventCategoryApplication;
		}
	};

	// event for a window resize, will record the window's current width, height
	class WindowResizeEvent : public Event {
	public:
		WindowResizeEvent(unsigned int width, unsigned int height) : m_WindowWidth(width), m_WindowHeight(height) {}

		unsigned int GetWidth() const { return m_WindowWidth; }

		unsigned int GetHeight() const { return m_WindowHeight; }

		static EventType GetStaticType() { return EventType::WindowResize; }

		EventType GetEventType() const { 
			return GetStaticType();
		}

		const char* GetName() const {
			return "WindowResize";
		}

		int GetCategoryFlags() const override {
			return EventCategoryApplication;
		}

		std::string ToString() const { 
			std::stringstream ss;
			ss << "Window Resize: (width: " << m_WindowWidth << ", height: " << m_WindowHeight << ")";
			return ss.str();
		}
	private:
		unsigned int m_WindowWidth, m_WindowHeight;
	};

	// below classes may implement later
	class WindowFocusEvent : public Event {

	};

	class WindowLostFocusEvent : public Event {

	};

	class WindowMovedEvent : public Event {

	};
}