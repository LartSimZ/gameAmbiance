namespace gameAmbiance
{
    namespace hw
    {
        class display_pixel_driver_interface
        {
        public:
            virtual void clear(uint32_t color) = 0;
            virtual void setPixel(int16_t x, int16_t y, uint32_t color) = 0;
            virtual void render() = 0;
        };
    }
}