classdef floatingPointConverter
    %FLOATINGPOINTCONVERTER Converter class for exporting floating-point
    %numbers as raw register data in hexadecimal format. 
    
    properties
        datatype   % floating point data type: 'FLOAT' or 'DOUBLE'
        dataorient % matrix data orientation: 'ROWS' or 'COLS'
    end
    
    methods
        
        function obj = floatingPointConverter(type,orient)
            %FLOATINGPOINTCONVERTER Construct an instance of this class.
            %   
            obj.datatype = type;
            obj.dataorient = orient;
        end
        
        function rslt_str = print_c_array(obj, varname, varsize, data)
            %PRINT_C_ARRAY Returns string with C code containing integer
            %array definition with 'data' in hex format.
            %   
            switch obj.datatype
                case 'FLOAT'
                    array_type = 'uint32_t';
                case 'DOUBLE'
                    array_type = 'uint64_t';
            end
            
            rslt_str = [sprintf('%s %s[%s] = {\n', array_type, varname, varsize) ...
                        obj.print_csv_hex_data(data), '};'];

        end % print_c_array
        
        function rslt_str = print_csv_hex_data(obj, data)
            %PRINT_CSV_HEX_DATA Prints input matrix as comma separeted
            %values in hexadecimal format.  
            %
            switch obj.datatype
                case 'FLOAT'
                    fp_to_hex = @obj.float_to_hex;
                case 'DOUBLE'
                    fp_to_hex = @obj.double_to_hex;
            end

            % Check data orientation (if matrix)
            if strcmp(obj.dataorient,'COLS')
                data = data'; % CMSIS compatible: row by row
            end

            % Create character vector from data
            rslt_str = ''; 

            R = size(data, 1);
            C = size(data, 2);
            
            for i = 1 : R
                for j = 1 : C-1
                    str_tmp = sprintf('  %s, ', fp_to_hex(data(i,j)));
                    rslt_str = [rslt_str, str_tmp];
                end
                if i < R
                    str_tmp = sprintf('  %s,\n',  fp_to_hex(data(i,end)));
                else
                    str_tmp = sprintf('  %s\n', fp_to_hex(data(i,end)));
                end
                rslt_str = [rslt_str, str_tmp];
            end   
        end % print_csv_hex_data

    end
    
    methods ( Access = private )
        
        function hex_str = double_to_hex(obj, d_val)
            % DOUBLE_TO_HEX Converts variable of type 'double' to raw register 
            % data in hexadecimal format    
        
            d = double(d_val);
            byte_array = typecast(d, 'uint64');
            hex_str = obj.int2hex(byte_array);
            hex_str = hex_str(:)';
            hex_str = ['0x' hex_str];
        end
        
        function hex_str = float_to_hex(obj, f_val)
            % FLOAT_TO_HEX Converts variable of type 'float' to raw register 
            % data in hexadecimal format  
        
            f = single(f_val);
            byte_array = typecast(f, 'uint32');
            hex_str = dec2hex(byte_array, 8);
            hex_str = hex_str(:)';
            hex_str = ['0x' hex_str];
        end
        
        function ret = int2hex(obj, var)        
        % INT2HEX Prints integer array to hexadecimal string
            varType = class(var);
            % cast signness away:
            if ('u' ~= varType(1) )
                varType = ['u' varType];
                var = typecast(var,varType);
            end        
            nBits = str2double(varType(5:end));
            if (64 == nBits) 
            % split 64 bit case into two 32's
            % cuz dec2hex doesn't handle 64 bit
                varType(5:end) = '32';
                var = typecast(var,varType);
            end

            ret = dec2hex(var);

            if (64 == nBits)
                littleEndian = all(typecast(uint32(1),'uint16')==[1 0]);
                first  = 1 + littleEndian;
                second = 2 - littleEndian;
                ret = [ret(first:2:end,:),ret(second:2:end,:)];
            end
        end % int2hex
        
    end
end

