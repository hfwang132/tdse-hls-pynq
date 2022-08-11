clear; clc;
h = 10;  % plotheight
I = 0.0+1.0i;

%======= parameters

tau = 1e-2;  % 1e-8
time = 5;

xnum = 10;  % size
ynum = xnum;
gridnum_x = 100;  % number of grid (must be odd)
gridnum_y = gridnum_x;
dx = xnum/gridnum_x;  % seperation
dy = dx;

b48 = -1/(48*pi^2*dx^2)*tau;  % beta
b3 = 1/(3*pi^2*dx^2)*tau;
c48 = cos(b48);
s48 = sin(b48);
c3 = cos(b3);
s3 = sin(b3);


%======= initialization =========
  % initialize a gaussian_sin wave packet
psi = zeros(gridnum_x,gridnum_y);
V = zeros(gridnum_x, gridnum_y);

sigma_x = xnum / 25;  % sigma_x
sigmai_x = sigma_x/dx;
sigma_y = xnum / 25;  % sigma_y
sigmai_y = sigma_y/dy;
inipos_x = 1 / 3;  % initial position x
i0 = gridnum_x*inipos_x;
inipos_y = 1 / 2;  % initial position x
j0 = gridnum_y*inipos_y;
k = pi / (2 * dx); %  wavenumber -pi < k*dx < pi, 


for i = 1 : gridnum_x
    for j = 1 : gridnum_y
        psi(i,j) = exp(I*k*i*dx)*exp(-((i-i0)^2/(2*sigmai_x^2))-((j-j0)^2/(2*sigmai_y^2))) / sqrt(pi * sigmai_y * sigmai_x);  % Gaussian
    end
end

thickness = 4; aperture = 6;
for i = 1 : gridnum_x
    if (i>floor(gridnum_x/2-thickness/2)) && (i<floor(gridnum_x/2+thickness/2))
        for j = 1 : gridnum_y
            if (j>floor(gridnum_y/2+aperture/2)) || (j<floor(gridnum_y/2-aperture/2))
                V(i,j) = 1e+30;  % Gaussian
            end
        end
    end
end

% for i = 1:gridnum_x
%     for j = 1:gridnum_y
%         V(i,j) = 0.01 * (i - 50) ^ 2 + 0.01 * (j - 50) ^ 2;
%     end
% end

%==========
norm = sum(sum(abs(psi).^2));  % check normalization

psi_new = psi;  % initialize the new wave function
iterstep = floor(time/tau);

framenum = time;  % frame number of the movie
timestamp = floor(iterstep/framenum); l = 0;

norm_change = zeros(iterstep,1);
[X, Y] = meshgrid(1:gridnum_x,1:gridnum_y);

R48 = [c48 I*s48; I*s48 c48];
R3 = [c3 I*s3; I*s3 c3];
vec = [0; 0];
%======= employ the algorithm
for k = 1 : iterstep
    %=======
    for i_ini = 1:4
        for i = i_ini:4:gridnum_x-2
            for j = 1:gridnum_y
%                 psi_new(i,j) = psi_new(i,j)*c48 + I*psi_new(i+2,j)*s48;
%                 psi_new(i+2,j) = I*psi_new(i,j)*s48 + psi_new(i+2,j)*c48;
%                 psi_tmp_1 = psi_new(i,j);
%                 psi_tmp_2 = psi_new(i+2,j);
%                 psi_new(i,j) = psi_tmp_1*c48 + I*psi_tmp_2*s48;
%                 psi_new(i+2,j) = I*psi_tmp_1*s48 + psi_tmp_2*c48;
                vec_tmp = [psi_new(i,j); psi_new(i+2,j)];
                vec = R48 * vec_tmp;
                psi_new(i,j) = vec(1);
                psi_new(i+2,j) = vec(2);
            end
        end
    end
    %=====
    for i_ini = 1:2
        for i = i_ini:2:gridnum_x-1
            for j = 1:gridnum_y
%                 psi_tmp_1 = psi_new(i,j);
%                 psi_tmp_2 = psi_new(i+1,j);
%                 psi_new(i,j) = psi_tmp_1*c3 + I*psi_tmp_2*s3;
%                 psi_new(i+1,j) = I*psi_tmp_1*s3 + psi_tmp_2*c3;
                vec_tmp = [psi_new(i,j); psi_new(i+1,j)];
                vec = R3 * vec_tmp;
                psi_new(i,j) = vec(1);
                psi_new(i+1,j) = vec(2);
            end
        end
    end
    %======== 
    for j_ini = 1:4
        for j = j_ini:4:gridnum_y-2
            for i = 1:gridnum_x
%                 psi_tmp_1 = psi_new(i,j);
%                 psi_tmp_2 = psi_new(i,j+2);
%                 psi_new(i,j) = psi_tmp_1*c48 + I*psi_tmp_2*s48;
%                 psi_new(i,j+2) = I*psi_tmp_1*s48 + psi_tmp_2*c48;
                vec_tmp = [psi_new(i,j); psi_new(i,j+2)];
                vec = R48 * vec_tmp;
                psi_new(i,j) = vec(1);
                psi_new(i,j+2) = vec(2);
            end
        end
    end
    %=====
    for j_ini = 1:2
        for j = j_ini:2:gridnum_y-1
            for i = 1:gridnum_x
%                 psi_tmp_1 = psi_new(i,j);
%                 psi_tmp_2 = psi_new(i,j+1);
%                 psi_new(i,j) = psi_tmp_1*c3 + I*psi_tmp_2*s3;
%                 psi_new(i,j+1) = I*psi_tmp_1*s3 +psi_tmp_2*c3;
                vec_tmp = [psi_new(i,j); psi_new(i,j+1)];
                vec = R3 * vec_tmp;
                psi_new(i,j) = vec(1);
                psi_new(i,j+1) = vec(2);
            end
        end
    end
    %=======
    for i = 1:gridnum_x
        for j = 1:gridnum_y
            v60 = - tau * (60 * (-b48) / tau + V(i,j));
%             c60 = 1 - v60^2/2;
%             s60 = v60;
            c60 = cos(v60);
            s60 = sin(v60);
            psi_tmp_1 = real(psi_new(i,j));
            psi_tmp_2 = imag(psi_new(i,j));

            psi_new_re = psi_tmp_1 * c60 - psi_tmp_2 * s60;
            psi_new_im = psi_tmp_1 * s60 + psi_tmp_2 * c60;
            psi_new(i,j) = psi_new_re + I * psi_new_im;

%             psi_new(i,j) = psi_new(i,j) * exp(I * v60);
        end
    end
    
%========
    if mod(k,timestamp) == 0   
        surf(X', Y', abs(psi_new))
        colorbar
        caxis([0 max(max(abs(psi)))]);
        shading interp
        set(gca,'DataAspectRatio',[1 1 1])
        axis([0 gridnum_x 0 gridnum_y -h*dx h*dx])
        view([0 0 1])

        l = l + 1;
        Movie(l) = getframe;
        disp(["frame: ", l])

        norm_new = sum(sum(abs(psi_new).^2));
        norm_change(k) = norm_new;
        disp(["norm: ", norm_new]); 
        disp(["c48 = ", c48]);
        disp(["c3 = ", c3]);
        disp(["s48 = ", s48]);
        disp(["s3 = ", s3]);
        disp(["v60 = ", v60]);
    end
end
%==========
movie(Movie,40);
%==========
plot(0:iterstep, [norm norm_change']);

