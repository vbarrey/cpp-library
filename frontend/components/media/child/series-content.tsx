"use client";

import { Series } from "@/lib/api";
import { motion } from "motion/react";
import { GenresList } from "./genres-list";
import { cn } from "@/lib/utils";
import { Rating } from "./rating";

type Props = {
    series: Series,
    expanded: boolean,
}

export function SeriesContent({ series, expanded }: Props) {
    return (
        <div className="min-w-0 flex-1 p-4">

            <div className="flex flex-row items-baseline gap-2">
                <h2 className={cn("font-bold truncate", expanded ? "text-5xl" : "text-base")}>
                    {series.title}
                </h2>

                <Rating rating={series.rating} />
            </div>

            <p className={cn("text-sm text-muted-foreground", expanded ? "text-lg" : "text-sm")}>
                {series.director}
            </p>

            <GenresList genres={series.genres} mediaId={series.id} />

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