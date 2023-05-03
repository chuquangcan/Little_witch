#ifndef TIMER_H
#define TIMER_H

class Timer
{
    public:
        Timer();
        virtual ~Timer();

        void start(); // dem thoi gian
        void stop();
        void paused();
        void unpaused();

        int get_ticks();

        bool is_started();
        bool is_paused();

    private:
        int start_tick;
        int pause_tick;

        bool is_pausing;
        bool is_starting;
};

#endif // TIMER_H
