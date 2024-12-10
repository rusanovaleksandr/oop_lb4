#include "../headers/ship.h"

Ship::Ship() : Ship(Length::ONE) {}

Ship::Ship(Length length) : Ship(length, ShipOrientation::HORIZONTAL) {}

Ship::Ship(Length length, ShipOrientation orientation) : length_(length), orientation_(orientation)
{
    for (std::size_t i = 0; i < this->length_; i++)
    {
        segments_.push_back(ShipSegmentState::INTACT);
    }
}

Ship::Ship(const Ship &other)
{
    length_ = other.length_;
    orientation_ = other.orientation_;
    segments_ = other.segments_;
}

Ship::Ship(Ship &&other)
{
    length_ = other.length_;
    orientation_ = other.orientation_;
    segments_ = std::move(other.segments_);
}

Ship &Ship::operator=(const Ship &other)
{
    if (this != &other)
    {
        this->length_ = other.length_;
        this->orientation_ = other.orientation_;
        this->segments_ = other.segments_;
    }
    return *this;
}

Ship &Ship::operator=(Ship &&other)
{
    if (this != &other)
    {
        this->length_ = other.length_;
        this->orientation_ = other.orientation_;
        this->segments_ = std::move(other.segments_);
    }
    return *this;
}

void Ship::setOrientation(ShipOrientation orientation)
{
    orientation_ = orientation;
}

void Ship::hitSegment(int index)
{
    if (index < 0 or index >= length_)
    {
        throw std::runtime_error("Wrong index");
    }
    if (segments_[index] == ShipSegmentState::INTACT)
    {
        segments_[index] = ShipSegmentState::DAMAGED;
    }
    else if (segments_[index] == ShipSegmentState::DAMAGED)
    {
        segments_[index] = ShipSegmentState::DESTROYED;
    }
    else if (segments_[index] == ShipSegmentState::DESTROYED)
    {
        throw SegmentAlreadyDestroyedException("Segment already destroyed");
    }
}

bool Ship::isDestroyed() const
{
    return std::all_of(segments_.begin(), segments_.end(), [](ShipSegmentState state)
                       { return state == ShipSegmentState::DESTROYED; });
}

const ShipSegmentState Ship::getSegmentAtIndex(int index) const
{
    return segments_.at(index);
}

const Length Ship::getLength() const
{
    return length_;
}

const ShipOrientation Ship::getOrientation() const
{
    return orientation_;
}


void Ship::setSegmentAtIndex(int index, ShipSegmentState state)
{
    segments_[index] = state;
}


json Ship::toJson() const
{
    json json_object;

    json_object["length"] = static_cast<int>(length_);

    if(orientation_ == ShipOrientation::HORIZONTAL)
    {
        json_object["orientation"] = "HORIZONTAL";
    }
    else
    {
        json_object["orientation"] = "VERTICAL";
    }

    json segments_array = json::array();
    for(const auto& segment : segments_)
    {
        switch (segment)
        {
            case ShipSegmentState::INTACT:
                segments_array.push_back("INTACT");
                break;
            case ShipSegmentState::DAMAGED:
                segments_array.push_back("DAMAGED");
                break;
            case ShipSegmentState::DESTROYED:
                segments_array.push_back("DESTROYED");
                break;
        }
    }
    json_object["segments"] = segments_array;

    return json_object;

}

void Ship::fromJson(const json& jsn)
{
    length_ = static_cast<Length>(jsn.at("length").get<int>());

    std::string orientation_str = jsn.at("orientation").get<std::string>();
    if(orientation_str == "HORIZONTAL")
    {
        orientation_ = HORIZONTAL;
    }
    else
    {
        orientation_ = VERTICAL;
    }

    segments_.clear();
    for(const auto& segment_str : jsn.at("segments"))
    {
        if(segment_str == "INTACT")
        {
            segments_.push_back(INTACT);
        }
        else if(segment_str == "DAMAGED")
        {
            segments_.push_back(DAMAGED);
        }
        else if(segment_str == "DESTROYED")
        {
            segments_.push_back(DESTROYED);
        }
    }
}

void Ship::setOrientation(char orientation_char)
{
    if (orientation_char == 'H' || orientation_char == 'h')
    {
        orientation_ = HORIZONTAL;
    } 
    else if (orientation_char == 'V' || orientation_char == 'v')
    {
        orientation_ = VERTICAL;
    } 
    else
    {
        throw std::invalid_argument("Invalid orientation");
    }
}