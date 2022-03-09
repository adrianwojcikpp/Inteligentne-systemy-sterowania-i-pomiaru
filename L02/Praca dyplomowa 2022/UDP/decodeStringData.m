function s = decodeStringData(a)
a_t = a';
a_u = native2unicode(a_t);
s = str2double(a_u);
end