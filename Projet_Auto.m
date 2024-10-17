clear all;
close all;
Ny      = 3;                  % Longueur de Y
Nu     = 1;                   % Longueur de U
A      = [1, -0.905,0];       %order 1
B      = [0.1,0];
%A      = [1, -1.511,0.549];  %order 2
%B      = [0,0.106];
na     = length(A) - 1;       % degree de A
nb     = length(B) - 1;       % degree de B
lambda  = 2;
N = 500;
Yc=ones(N,1);
Yc(101:200,1)*=2;
Yc(301:400,1)*=2;
Y=zeros(N,1);

F=zeros(3,3);                 % initialisattion de F
F(1,:)=[1-A(2),A(2)-A(3),A(3)];
F(2,:)=[(A(2)-1)^2+A(2)-A(3),A(3)-(A(3)-A(2))*(1-A(2)),A(3)*(1-A(2))];
F(3,:)=[A(3)+(1-A(2))^3+2*(A(3)-A(2))*(A(2)-1) ,(1-A(2))*A(3)-(A(3)-A(2))*((1-A(2))^2-(A(3)-A(2))),A(3)*((1-A(2))^2-(A(3)-A(2))) ];

E=zeros(3,3);                 % initialisattion de E
E(1,:)=[1,0,0];
E(2,:)=[1,(1-A(2)),0];
E(3,:)=[1,(1-A(2)),(1-A(2))^2-(A(3)-A(2))];

g=zeros(3,1);
g(:,1)=[B(1),((1-A(2))*B(1))+B(2),B(2)*(1-A(2))+B(1)*(A(2)-A(3)+(-A(2)+1)^2)];

H=B(2)*[1,(1-A(2)),(1-A(2))^2-(A(3)-A(2))];

G1=zeros(3,3);
G1(:,1)=g(:,1);
G1(2:3,2)=g(1:2,1);
G1(3,3)=g(1,1);

G=G1(:,1:Nu);
u=zeros(N, 1);

du=1;

for k=3:N-3
  Y(k)=-A(2)*Y(k-1)-A(3)*Y(k-2)+B(1)*u(k-1)+B(2)*u(k-2);
  for i=1:Ny
    Y0(i) = F(i,1)*Y(k)+F(i,2)*Y(k-1)+F(i,3)*Y(k-2)+H(i)*du;
  end
L=inverse(transpose(G)*G+lambda*eye(Ny-Nu));
V=L*(transpose(G)*(Yc(k+1:k+3)-Y0'));
du=V(1);
u(k)=du+u(k-1);
end

figure(1)
plot(1:497,Yc(1:497));
hold on
plot(1:497,Y(1:497));
hold on
plot(1:497,u(1:497));
xlabel("temps ")
ylabel("sortie")
legend('Yc(k)','Y(k)','U(k)');
