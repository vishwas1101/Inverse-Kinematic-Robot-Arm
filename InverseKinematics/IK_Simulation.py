import math
import matplotlib.pyplot as plt

def getPoint(x, y, z, base, arm1, arm2, alpha):

    e = (x**2 + y**2 + z**2 - base**2 + arm1**2 - arm2**2)/2

    if(x!=0 or y!=0):
        a1 = ((((z-base)**2)*(1+math.tan(alpha)**2))/((x + y*math.tan(alpha))**2)) + 1
        b1 = 2*((e*(z-base)*(1 + math.tan(alpha)**2))/((x + y*math.tan(alpha))**2) + base)
        c1 = ((e**2)*(1 + math.tan(alpha)**2))/((x + y*math.tan(alpha))**2) + base**2 - arm1**2

        d1 = (b1**2 - 4*a1*c1)**0.5

        c = (b1 + d1)/(2*a1)
        a = (e - c*(z-base))/(x + y*math.tan(alpha))
        b = a*math.tan(alpha)
    else:
        a = 0
        b = 0
        c = 50
    return a, b, c
    
def getAngle(x, y, z, base, arm1, arm2):

    d = (x**2 + y**2 + (z-base)**2)**0.5

    if(x!=0):
        alpha = math.atan(y/x)
    else:
        alpha = math.pi/2

    theta1 = math.asin((z-base)/d)
    theta2 = math.acos((arm1**2 + d**2 - arm2**2)/(2*arm1*d))
    
    beta =  theta1 + theta2

    gamma = math.acos((arm1**2 + arm2**2 - d**2)/(2*arm1*arm2))

    alpha = math.degrees(alpha)
    beta = math.degrees(beta)
    gamma = math.degrees(gamma)

    
    return alpha, beta, gamma
    
base, arm1, arm2 = [int(x) for x in input("Enter length of base and arm1 and arm2: ").split(" ")]

x, y, z = [int(x) for x in input("Enter value of x,y,z: ").split(" ")]

if ((math.sqrt(x**2 + y**2 + (z-base)**2)) <= arm1 + arm2):

    fig = plt.figure()
    ax = fig.add_subplot(111)
    
    angBase, angArm1, angArm2 = getAngle(x, y, z, base, arm1 ,arm2)
    pointX, pointY, pointZ = getPoint(x, y, z, base, arm1, arm2, angBase)

    point = [pointX,pointY,pointZ]
    print(point);
    
    X = [0, 0, pointX, x]
    Y = [0, 0, pointY, y]
    Z = [0, base, pointZ, z]

    print("Angle of Base = ", angBase)
    print("Angle of Arm1 = ", angArm1)
    print("Angle of Arm2 = ", angArm2)
    
    plt.plot(X,Z)
    plt.show()
else:
    print("The point cant be reached")
