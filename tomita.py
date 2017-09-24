# -*- encoding: utf-8 -*-
import os
import subprocess
import xml.etree.ElementTree as ElementTree


class TomitaParser(object):
    def __init__(self, executable, config, debug=True, validate=True):
        self.debug_mode = debug
        self.debug("Init Tomita Parser...")

        self.executable = os.path.expanduser(executable)
        if not os.path.exists(self.executable):
            raise Exception("Tomita executable not found at: %s" % self.executable)

        self.debug("Executable: %s" % self.executable)

        self.config = os.path.expanduser(config)
        if not os.path.exists(self.config):
            raise Exception("Config file not found at: %s" % self.config)

        self.debug("Config: %s" % self.config)

        self.path = self.config[:self.config.rfind("/")]

        self.debug("Path: %s" % self.path)
        self.debug("ZBS!")

        if validate:
            self.validate_config()

    def validate_config(self):
        is_xml = False
        with open(self.config, "r") as f:
            for line in f.readlines():
                line = line.strip()
                if line:
                    if line.startswith("File"):
                        raise Exception("This library uses STDIN and STDOT for communicating with Tomita Parser, "
                                        "please remove all File = \"...\" from Input and Output sections in config.")
                    if line.startswith("Format") and "xml" in line:
                        is_xml = True
        if not is_xml:
            raise Exception("This library working only with XML output, "
                            "please add \"Format = xml;\" to the Output section.")

    def run(self, text, with_facts=True, with_leads=True):
        self.debug("Running Tomita Parser...")
        
        try:
            out = subprocess.check_output([self.executable, self.config], input=text.encode("utf-8")).decode("utf-8")            
        except:
            pipe.kill()
            self.debug(out)

        facts = []
        leads = []
        etree_root = ElementTree.fromstring(out)
        if etree_root.find("document") is not None:
            if with_facts:
                self.debug("Parsing facts...")
                for fact in etree_root.find("document").find("facts"):
                    
                    if fact.find("LeftText") is not None:
                        facts.append({
                            "fact_id": fact.attrib.get("FactID"),
                            "lead_id": fact.attrib.get("LeadID"),
                            "pos": fact.attrib.get("pos"),
                            "len": fact.attrib.get("len"),
                            "fact_main": fact.find("Main").attrib.get("val"),
                            "fact_left": fact.find("LeftText").attrib.get("val"),
                            "fact_right":  ''
                        })
                    elif fact.find("RightText") is not None:
                        facts.append({
                            "fact_id": fact.attrib.get("FactID"),
                            "lead_id": fact.attrib.get("LeadID"),
                            "pos": fact.attrib.get("pos"),
                            "len": fact.attrib.get("len"),
                            "fact_main": fact.find("Main").attrib.get("val"),
                            "fact_left": '',
                            "fact_right": fact.find("RightText").attrib.get("val")
                        })
                    else:
                        facts.append({
                            "fact_id": fact.attrib.get("FactID"),
                            "lead_id": fact.attrib.get("LeadID"),
                            "pos": fact.attrib.get("pos"),
                            "len": fact.attrib.get("len"),
                            "fact_main": fact.find("Main").attrib.get("val"),
                            "fact_left": fact.find("LeftText").attrib.get("val"),
                            "fact_right": fact.find("RightText").attrib.get("val")
                        })
                        
                        

            if with_leads:
                self.debug("Parsing leads...")
                for lead in etree_root.find("document").find("Leads"):
                    leads.append({
                        "lead_id": lead.attrib.get("id"),
                        "lead": lead.attrib.get("text")
                    })

        return facts, leads

    def debug(self, text):
        if self.debug_mode:
            print("####: "+text)