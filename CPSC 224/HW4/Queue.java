//	Kevin Andrew Hance
//	February 22nd, 2018
//	Object Oriented Programming
//	HW Assignment #4: Queue
//
//  This program creates a First-Come-First-Serve (FCFS) data structure using an Array for keeping track
//	of tasks that need to be completed. There are two forms of the Queue data structure: a normal 
//	"Queue", and a "PriorityQueue" with slightly more functionality. PriorityQueue allows the user
//	to define a priority for the task, where higher priorities are "completed" first when dequeue()
//	is called. The normal Queue just uses the FCFS order when "completing" tasks.

import java.util.*;
import java.io.*;

public class Queue {
	
	static int maxSize = 100;
	Task[] taskList;
	int front;
	int back;
	int count;
	int queueSize;
	
	public static void main (String[] args) {
		
		PriorityQueue q = new PriorityQueue(10);
		q.enqueue(new Task("Eat your vegetables", 2));
		q.enqueue(new Task("Take the trash out", 1));
		q.enqueue(new Task("Go to work", 3));
		q.enqueue(new Task("Take the recycle out", 4));
		q.enqueue(new Task("Stop by Safeway", 5));
		q.dequeue();
		
		q.enqueue(new Task("Change oil in the Toyota", 6));
		q.enqueue(new Task("Update accounting software", 2));
		q.enqueue(new Task("Wash the dishes", 5));
		q.enqueue(new Task("Do CPEN pre-lab", 5));
		q.display();
		
		
		q.dequeue();
		q.dequeue();
		q.dequeue();
		q.dequeue();
		q.display();
		
		q.dequeue();
		q.dequeue();
		q.display();
		
		q.dequeue();
		q.dequeue();
		q.dequeue();
		q.display();
		
		q.dequeue();
		q.dequeue();
		q.display();
		
		System.out.println("\nNow that we've filled up and emptied the Priority Queue, we will test the normal Queue.");
		
		Queue q2 = new Queue(10);
		
		q2.enqueue(new Task("Take the trash out"));
		q2.display();
		
		q2.enqueue(new Task("Feed the fish"));
		q2.enqueue(new Task("Walk Brenda's dog"));
		q2.enqueue(new Task("Visit Jake at work"));
		q2.display();
		
		q2.enqueue(new Task("Fill car with gas"));
		q2.enqueue(new Task("Go to class"));
		q2.enqueue(new Task("Bring the garbage bin back up the driveway"));
		q2.display();
		
		q2.enqueue(new Task("Empty the dishwasher"));
		q2.enqueue(new Task("Make the bed in the guest room"));
		q2.display();
		
		q2.dequeue();
		q2.dequeue();
		q2.dequeue();
		q2.dequeue();
		q2.display();
		
		q2.dequeue();
		q2.dequeue();
		q2.dequeue();
		q2.dequeue();
		q2.display();
		
		q2.dequeue();
		q2.dequeue();
		q2.display();
	}
	
	public Queue() {
		taskList = new Task[maxSize];
		front = 0;
		back = 0;
		count = 0;
		queueSize = maxSize;
	}
	
	public Queue(int size) {
		taskList = new Task[size];
		front = 0;
		back = 0;
		count = 0;
		queueSize = size;
	}
	
	public boolean isEmpty() {
		return (count == 0);
	}
	
	public boolean isFull() {
		return (count == queueSize);
	}
	
	public void enqueue(Task newTask) {
		if(isEmpty()) {
			taskList[front] = newTask;
			back++;
			count++;
		} else if(isFull()) {
			System.out.println("Queue is full, task can not be added.\n");
		} else {
			// add item to back regardless of priority
			taskList[back] = newTask;
			back++;
			count++;
		}
	}
	
	public void dequeue() {		
		if(!isEmpty()) {
			shiftLeft();
			count--;
		} else {
			System.out.println("Queue is empty, dequeue can not be executed on an empty queue.\n");
		}
	}
	
	public void display() {
		if (!isEmpty()) {	
			for(int i = front; i < back; i++) {
				System.out.println("Index: " + i + "\tTask: " + taskList[i].getDescription());
			}
			System.out.println();
		} else {
			System.out.println("Queue is empty\n");
		}
	}
	
	public boolean shiftLeft() {
		if(!isEmpty()) {
			for (int i = 0; i < back - 1; i++) {
				taskList[i] = taskList[i+1];
			}
			back--;
			return true;
		} else {
			return false;
		}
	}
}

class PriorityQueue extends Queue {
	
	public PriorityQueue() {
		taskList = new Task[maxSize];
		front = 0;
		back = 0;
		count = 0;
		queueSize = maxSize;
	}
	
	public PriorityQueue(int size) {
		taskList = new Task[size];
		front = 0;
		back = 0;
		count = 0;
		queueSize = size;
	}
	
	public void enqueue(Task newTask) {
		if(isEmpty()) {
			taskList[0] = newTask;
			back++;
			count++;
		} else if(!isFull()) {
			int indexToAddElementTo = back;
			
			// first, find index we need to place item in based on priority
			indexToAddElementTo = findIndexToAddElementTo(newTask.getPriority());
			
			// next, we need to clear that spot in memory
			if(indexToAddElementTo < back)
				shiftRight(indexToAddElementTo);
			//then, place element in taskList
			taskList[indexToAddElementTo] = newTask;
			back++;
			count++;
		} else {
			System.out.println("Queue is full, task can not be added.\n");
		}
	}
	
	public void dequeue() {
		super.dequeue();
	}
	
	public void display() {
		if(!isEmpty()) {
			for(int i = front; i < back; i++) {
				System.out.println("Index: " + i + "\tTask Priority: " + taskList[i].getPriority() + "\tTask: " + taskList[i].getDescription());
			}
			System.out.println();
		} else {
			System.out.println("Queue is empty\n");
		}
	}
	
	public void shiftRight(int indexToBeFreed) {
		// shift right
		for(int i = back-1; i >= indexToBeFreed; i--) {
			taskList[i+1] = taskList[i];
		}
	}
	
	public int findIndexToAddElementTo(int priority) {
		if(!isEmpty()) {
			for (int i = 0; i < back; i++) {
				if(taskList[i].getPriority() < priority) {
					 return i;
				}
			}
			return back;
			
		} else {
			return 0;
		}
		
		
	}
	
}

class Task {
	
	private String taskDescription;
	private int taskPriority;
	
	public Task() {
		taskDescription = "default_task_name";
		taskPriority = 1;
	}
	
	public Task(String name) {
		taskDescription = name;
		taskPriority = 1;
	}
	
	public Task(String name, int priority) {
		taskDescription = name;
		taskPriority = priority;
	}
	
	public String getDescription() {
		return taskDescription;
	}
	
	public int getPriority() {
		return taskPriority;
	}
	
	public void setDescription(String desc) {
		taskDescription = desc;
	}
	
	public void setPriority(int pr) {
		taskPriority = pr;
	}
}