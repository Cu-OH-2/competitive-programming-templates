import os
import codecs

def batch_encoding_conversion(path):
    # 遍历目录下的文件
    for root, dirs, files in os.walk(path):
        print (f"dir:{dirs} files:{files}")
        for file in files:
            file_path = os.path.join(root, file)
            if file.endswith('.cpp'):
                with codecs.open(file_path, 'r', 'gb2312') as f:
                    content = f.read()
                    content_utf8 = content.encode('utf-8', 'ignore').decode('utf-8')
                    with codecs.open(file_path, 'w', 'utf-8') as f2:
                        f2.write(content_utf8)

batch_encoding_conversion('.')