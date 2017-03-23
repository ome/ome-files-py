# #%L
# OME-FILES Python library for image IO.
# Copyright (c) 2017 University of Dundee
# %%
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.
# #L%

import xml.dom.minidom as minidom
TEXT_NODE = minidom.Node.TEXT_NODE


def get_text(node):
    c = node.firstChild
    if c is None or c.nodeType != TEXT_NODE:
        raise ValueError("node %r does not contain text" % (node,))
    return c.data


def get_children(node):
    return [_ for _ in node.childNodes if _.nodeType != TEXT_NODE]


class NodeWrapper(object):

    FIELDS = []

    def __setattr__(self, name, value):
        if name not in self.FIELDS:
            raise AttributeError("attribute %s not allowed in %s" %
                                 (name, self.__class__.__name__))
        super(NodeWrapper, self).__setattr__(name, value)

    @classmethod
    def fromnode(cls, node):
        if node.nodeName != cls.__name__:
            raise ValueError("unexpected node: %s" % node.nodeName)
        w = cls()
        for name, value in node.attributes.items():
            setattr(w, name, value)
        super(NodeWrapper, w).__setattr__("_children", get_children(node))
        return w


class Annotation(NodeWrapper):

    FIELDS = ["Annotator", "ID", "Namespace", "Description", "AnnotationRef"]

    @classmethod
    def fromnode(cls, node):
        ann = super(Annotation, cls).fromnode(node)
        ann.AnnotationRef = []
        for c in ann._children:
            if c.nodeName == "Description":
                ann.Description = get_text(c)
            if c.nodeName == "AnnotationRef":
                ann.AnnotationRef.append(c.attributes.get("ID").value)
        return ann


class MapAnnotation(Annotation):

    FIELDS = Annotation.FIELDS + ["Value"]

    @classmethod
    def fromnode(cls, node):
        ann = super(MapAnnotation, cls).fromnode(node)
        ann.Value = {}
        for c in ann._children:
            if c.nodeName == "Value":
                for m in get_children(c):
                    try:
                        k = m.attributes.get("K").value
                    except AttributeError:
                        pass  # The "K" attribute is optional
                    else:
                        ann.Value.setdefault(k, []).append(get_text(m))
        return ann


class XMLAnnotation(Annotation):

    FIELDS = Annotation.FIELDS + ["Value"]

    @classmethod
    def fromnode(cls, node):
        ann = super(XMLAnnotation, cls).fromnode(node)
        for c in ann._children:
            if c.nodeName == "Value":
                ann.Value = c
        return ann


class OMEXMLMetadata(object):

    def __init__(self, xml_string):
        self.doc = minidom.parseString(xml_string)

    def get_map_annotations(self):
        return [MapAnnotation.fromnode(_) for _ in
                self.doc.getElementsByTagName("MapAnnotation")]

    def get_xml_annotations(self):
        return [XMLAnnotation.fromnode(_) for _ in
                self.doc.getElementsByTagName("XMLAnnotation")]
