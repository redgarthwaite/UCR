package nachos.threads;

import nachos.machine.*;
import java.util.PriorityQueue;
/**
 * Uses the hardware timer to provide preemption, and to allow threads to sleep
 * until a certain time.
 */


public class Alarm {
	public class WaitingThread
	{	
		private long time;
		public KThread thread;
		public WaitingThread()
		{
			thread = KThread.currentThread(); 
		}
		public void setTime(long x)
		{
			time = x;
		}
		public long getTime()
		{
			return time;
		}
	}
	
	PriorityQueue<WaitingThread> waitingThreads = new PriorityQueue<WaitingThread>();
    /**
     * Allocate a new Alarm. Set the machine's timer interrupt handler to this
     * alarm's callback.
     *
     * <p><b>Note</b>: Nachos will not function correctly with more than one
     * alarm.
     */
    public Alarm() {
	Machine.timer().setInterruptHandler(new Runnable() {
		public void run() { timerInterrupt(); }
	    });
    }

    /**
     * The timer interrupt handler. This is called by the machine's timer
     * periodically (approximately every 500 clock ticks). Causes the current
     * thread to yield, forcing a context switch if there is another thread
     * that should be run.
     */
    public void timerInterrupt() {
		Lib.assertTrue(Machine.interrupt().disabled());
//		System.out.println("Current Machine time is " + Machine.timer().getTime() );
		KThread.currentThread().yield();
		for(int i = 0; i < waitingThreads.size(); ++i)//queue length
		{
			if((waitingThreads.peek().getTime() <= Machine.timer().getTime()) && !(waitingThreads.isEmpty()))
			{
			//	System.out.println("Thread " + waitingThreads.peek().toString() + " woke up at " + Machine.timer().getTime() );
				waitingThreads.peek().thread.ready();
				waitingThreads.remove();
			}
		}
		return;
    }

    /**
     * Put the current thread to sleep for at least <i>x</i> ticks,
     * waking it up in the timer interrupt handler. The thread must be
     * woken up (placed in the scheduler ready set) during the first timer
     * interrupt where
     *
     * <p><blockquote>
     * (current time) >= (WaitUntil called time)+(x)
     * </blockquote>
     *
     * @param	x	the minimum number of clock ticks to wait.
     *
     * @see	nachos.machine.Timer#getTime()
     */

    public void waitUntil(long x) {

    Machine.interrupt().disable();
	long wakeTime = Machine.timer().getTime() + x;
	WaitingThread wait = new WaitingThread();
	wait.setTime(wakeTime);
	waitingThreads.add(wait);
//	System.out.println("Thread " + wait.toString() + " is falling asleep at " + Machine.timer().getTime() + " and should wake up in " + wakeTime );
	KThread.currentThread().sleep();
	Machine.interrupt().enable();
	return;
    }
    public void test()
    {
   // 	KThread t1 = new KThread();
   // 	KThread t2 = new KThread();
    	waitUntil(100);
    	waitUntil(50);
    	waitUntil(50);
    }
}
