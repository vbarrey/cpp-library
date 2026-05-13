"use client";

import { Series } from "@/lib/api";
import { motion } from "motion/react";

type Props = {
    series: Series,
    expanded: boolean,
}

export function SeriesContent({ series, expanded }: Props) {
    return (
        <div className="min-w-0 flex-1 p-4">
            <h2 className="font-bold truncate">
                {series.title}
            </h2>

            <p className="text-sm text-muted-foreground">
                {series.director}
            </p>

            {expanded && (

                <motion.div
                    initial={{
                        opacity: 0,
                        y: 10,
                    }}

                    animate={{
                        opacity: 1,
                        y: 0,
                    }}

                    transition={{
                        delay: 0.2,
                    }}
                >

                    <p className="mt-4 text-sm leading-relaxed">
                        {series.description}
                    </p>

                    <p className="mt-4 text-sm leading-relaxed">
                        {series.seasons} saisons
                    </p>
                </motion.div>
            )}

        </div>
    );
}