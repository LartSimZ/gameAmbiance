namespace gameAmbiance
{
    namespace hw
    {
        class display_pixel_driver_interface
        {
        public:
            virtual void clear(bool on) = 0;
            virtual void setPixel(int16_t x, int16_t y, bool on) = 0;
            virtual void render() = 0;
        };
    }
}