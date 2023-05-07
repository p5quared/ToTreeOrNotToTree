import pdfkit
from flask import Flask, request, send_from_directory

app = Flask(__name__)

app.config['INPUT_FOLDER'] = 'input'
app.config['OUTPUT_FOLDER'] = 'output'


@app.route('/', methods=['GET'])
def hello_world():
    return 'Hello World!'


@app.route('/api', methods=['POST', 'PUT'])
def api():
    if 'file' not in request.files:
        print('No file part', flush=True)
        return 'No file part'
    file = request.files['file']
    if file.filename == '':
        print('No selected file', flush=True)
        return 'No selected file'
    if file:
        file.save("input.html")
        convert_to_pdf("input.html")
        return send_from_directory(app.config['OUTPUT_FOLDER'], "output.pdf", as_attachment=True)


def convert_to_pdf(filename):
    pdfkit.from_file(filename, "output.pdf")



if __name__ == '__main__':
    app.run(host='0.0.0.0', port=8080)
