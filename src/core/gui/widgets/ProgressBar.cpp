#include "ProgressBar.h"
#include <iostream>

namespace ire::core::gui
{
    WidgetType const ProgressBar::m_type = WidgetType::create<ProgressBar>("ProgressBar");

    ProgressBar::ProgressBar()
	{
		m_rectangleShape.setFillColor(sf::Color::Blue);
		m_progressShape.setFillColor(sf::Color::Green);
		m_percent = static_cast<float>(m_value) / static_cast<float>(m_maximum);
		std::cout << m_percent << "\n";
	}

	std::unique_ptr<ProgressBar> ProgressBar::create(const std::string& text)
	{
		auto widget = std::make_unique<ProgressBar>();

		return widget;
	}

	void ProgressBar::draw(sf::RenderTarget& target)
	{
		target.draw(m_rectangleShape);
		target.draw(m_progressShape);
	}

	void ProgressBar::updateWidget()
	{
		m_rectangleShape.setSize(m_size);
		m_rectangleShape.setPosition(m_position);
		m_percent = static_cast<float>(m_value) / static_cast<float>(m_maximum);
		m_progressShape.setSize({m_size.x * m_percent, m_size.y});
		m_progressShape.setPosition(m_position);
	}
	void ProgressBar::setMinimum(unsigned int minimum)
	{
		if (m_minimum != minimum)
		{
			m_minimum = minimum;
		}
	}
	const unsigned int ProgressBar::getMinimum() const
	{
		return m_minimum;
	}
	void ProgressBar::setMaximum(unsigned int maximum)
	{
		if (m_maximum != maximum)
		{
			m_maximum = maximum;
		}
	}
	const unsigned int ProgressBar::getMaximum() const
	{
		return m_maximum;
	}
	void ProgressBar::setValue(unsigned int value)
	{
		if (m_value != value)
		{
			m_value = value;
		}
	}
	const unsigned int ProgressBar::getValue() const
	{
		return m_value;
	}
	void ProgressBar::setText(std::string& text)
	{
		if (m_textString != text)
		{
			m_textString = text;
		}
	}
	const std::string ProgressBar::getText() const
	{
		return m_textString;
	}
	void ProgressBar::setTextSize(unsigned int textSize)
	{
		if (m_textSize != textSize)
		{
			m_textSize = textSize;
		}
	}
	const unsigned int ProgressBar::getTextSize() const
	{
		return m_textSize;
	}
	void ProgressBar::setFillDirection(FillDirection fillDirection)
	{
		if (m_fillDirection != fillDirection)
		{
			m_fillDirection = fillDirection;
		}
	}
	const ProgressBar::FillDirection ProgressBar::getFillDirection() const
	{
		return m_fillDirection;
	}
	void ProgressBar::onEvent(EventRoot& sender, KeyDownEvent& ev)
	{
		switch (ev.key)
		{
		case sf::Keyboard::Left:
			std::cout << "Left\n";
			if (m_value > 0)
			{
				--m_value;
			}
			break;
		case sf::Keyboard::Right:
			std::cout << "Right\n";
			if (m_value < m_maximum)
			{
				++m_value;
			}
			break;
		default:
			break;
		}
		ev.handled = true;
		updateWidget();
		onKeyClicked(ev);
	}

	void ProgressBar::onKeyClicked(KeyDownEvent& ev)
	{
		KeyPressedEvent keyClickedEv{};
		keyClickedEv.timestamp = ev.timestamp;
		keyClickedEv.key = ev.key;
		keyClickedEv.alt = ev.alt;
		keyClickedEv.control = ev.control;
		keyClickedEv.shift = ev.control;
		keyClickedEv.system = ev.system;
		emitEvent<KeyPressedEvent>(keyClickedEv);
	}

}