from pylab import *

datafile = open('../data/lab05_g06_data.csv')

rerun_number, iteration_value, step_time, collision_time, velocity_time, position_time, loop_time = [],[],[],[],[],[],[]

while True:
    line=datafile.readline()
    if ',' not in line:
        break
    fields = line.split(',')
    rerun_number.append (int (fields[0]))
    iteration_value.append (int (fields[1]))
    step_time.append (float (fields[2]))
    collision_time.append (float (fields[3]))
    velocity_time.append (float (fields[4]))
    position_time.append (float (fields[5]))
    loop_time.append (float (fields[6]))

numValues=len(iteration_value)
numReruns=rerun_number[numValues-1]
numIterations=iteration_value[numValues-1]

# A plot showing the step time averaged over all reruns (Y) for various iteration values (X). 
# Plot the loop time averaged over all reruns (Y) for various iteration values (X) on the same graph.

avg_step = [0]*numIterations
avg_loop = [0]*numIterations

for index in range(numValues):
    avg_step[iteration_value[index]-1] = avg_step[iteration_value[index]-1]+step_time[index]
    avg_loop[iteration_value[index]-1] = avg_loop[iteration_value[index]-1]+loop_time[index]

for index in range(numIterations):
    avg_step[index] = avg_step[index]/numReruns
    avg_loop[index] = avg_loop[index]/numReruns

x=range(numIterations)
figure(0)
plot(x,avg_step)
plot(x,avg_loop)
savefig("g06_lab09_plot01.png")

#A plot showing the step time averaged over all reruns (Y) for various iteration values (X).
# Also, plot the collision time, velocity and poition update times averaged over all reruns (Y) for various iteration values (X) on the same graph. 

avg_collision = [0]*numIterations
avg_velocity = [0]*numIterations
avg_position = [0]*numIterations

for index in range(numValues):
    avg_collision[iteration_value[index]-1] = avg_collision[iteration_value[index]-1]+collision_time[index]
    avg_velocity[iteration_value[index]-1] = avg_velocity[iteration_value[index]-1]+velocity_time[index]
    avg_position[iteration_value[index]-1] = avg_position[iteration_value[index]-1]+position_time[index]

for index in range(numIterations):
    avg_collision[index] = avg_collision[index]/numReruns
    avg_velocity[index] = avg_velocity[index]/numReruns
    avg_position[index] = avg_position[index]/numReruns

figure(1)
plot(x,avg_step)
plot(x,avg_collision)
plot(x,avg_velocity)
plot(x,avg_position)
savefig("g06_lab09_plot02.png")

#Do the same plots as avg_rerun1, with the quantity on the Y axis now averaged over all iteration values (Y) for various reruns (X).

avg_step = [0]*numReruns
avg_loop = [0]*numReruns

for index in range(numValues):
    avg_step[rerun_number[index]-1] = avg_step[rerun_number[index]-1]+step_time[index]
    avg_loop[rerun_number[index]-1] = avg_loop[rerun_number[index]-1]+loop_time[index]

for index in range(numReruns):
    avg_step[index] = avg_step[index]/numIterations
    avg_loop[index] = avg_loop[index]/numIterations

x=range(numReruns)
figure(2)
plot(x,avg_step)
plot(x,avg_loop)
savefig("g06_lab09_plot03.png")

#Do the same plots as avg_rerun2, with the quantity on the Y axis now averaged over all iteration values (Y) for various reruns (X).

avg_collision = [0]*numReruns
avg_velocity = [0]*numReruns
avg_position = [0]*numReruns

for index in range(numValues):
    avg_collision[rerun_number[index]-1] = avg_collision[rerun_number[index]-1]+collision_time[index]
    avg_velocity[rerun_number[index]-1] = avg_velocity[rerun_number[index]-1]+velocity_time[index]
    avg_position[rerun_number[index]-1] = avg_position[rerun_number[index]-1]+position_time[index]

for index in range(numIterations):
    avg_collision[index] = avg_collision[index]/numIterations
    avg_velocity[index] = avg_velocity[index]/numIterations
    avg_position[index] = avg_position[index]/numIterations

figure(3)
plot(x,avg_step)
plot(x,avg_collision)
plot(x,avg_velocity)
plot(x,avg_position)
savefig("g06_lab09_plot04.png")

#Consider the variation in time over reruns to be the deviation in the time measurement and plot the step time for various iteration values with error bars corresponding to the deviation. 
